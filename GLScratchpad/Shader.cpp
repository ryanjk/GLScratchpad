#include "Shader.h"

#include <vector>

#include "directories.h"
#include "Util.h"
#include "Texture.h"

namespace glsp {

Shader::Shader(const std::string& shader_name) : shader_name_(shader_name) {
	Load();
}

Shader::~Shader() {
	glDeleteProgram(program_);
}

const std::string ShaderTypeToFilename(ShaderType type) {
	switch (type) {
	case ShaderType::VERTEX: return "vs.glsl";
	case ShaderType::GEOMETRY: return "gs.glsl";
	case ShaderType::TESSELLATION: return "ts.glsl";
	case ShaderType::FRAGMENT: return "fs.glsl";
	}
}

GLenum ShaderTypeToGL(ShaderType type) {
	switch (type) {
	case ShaderType::VERTEX: return GL_VERTEX_SHADER;
	case ShaderType::GEOMETRY: return GL_GEOMETRY_SHADER;
	//case ShaderType::TESSELLATION: return GL_TESSELLATION_SHADER;
	case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
	}
}

GLuint CreateShaderFromSource(ShaderType shader_type, const std::string& shader_source) {
	auto shader_handle = glCreateShader(ShaderTypeToGL(shader_type));
	auto shader_cstr = shader_source.c_str();
	glShaderSource(shader_handle, 1, &shader_cstr, NULL);
	glCompileShader(shader_handle);

	GLint success = 0;
	glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint log_size = 0;
		glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &log_size);
		std::vector<char> log(log_size);
		glGetShaderInfoLog(shader_handle, log_size, &log_size, &log[0]);
		PrintLine(&log[0]);

		return 0;
	}

	return shader_handle;
}

GLuint Shader::LoadShader(ShaderType type) {
	static const std::string SHADER_DIRECTORY = resource_dir + "Shader\\";
	const std::string full_path = SHADER_DIRECTORY + shader_name_ + "\\" + ShaderTypeToFilename(type);
	std::ifstream file(full_path);
	if (file.fail()) {
		PrintLine("Couldn't load shader at " + full_path);
		return 0;
	}
	std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return CreateShaderFromSource(type, source);
}

void Shader::Load() {	

	GLuint vs = LoadShader(ShaderType::VERTEX);
	GLuint fs = LoadShader(ShaderType::FRAGMENT);
	GLuint gs = LoadShader(ShaderType::GEOMETRY);
	const std::vector<GLuint> shaders = { vs, fs, gs };

	GLuint program = glCreateProgram();
	for (auto shader : shaders) {
		if (shader == 0) continue;
		glAttachShader(program, shader);
	}
	glLinkProgram(program);

	GLint success = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		GLint log_size = 0;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &log_size);
		std::vector<char> log(log_size);
		glGetShaderInfoLog(program, log_size, &log_size, &log[0]);
		PrintLine(&log[0]);
		program_ = 0;
		return;
	}

	for (auto shader : shaders) {
		if (shader == 0) continue;
		glDeleteShader(shader);
	}

	program_ = program;
}

void Shader::Use() const {
	glUseProgram(program_);
}

GLuint Shader::GetProgram() const {
	return program_;
}

GLuint Shader::GetUniformLocation(const char* id) {
	auto location = glGetUniformLocation(program_, id);
	if (location == -1) {
		PrintLine(std::string("Could not find uniform with id '") + id + "' in shader " + shader_name_);
	}
	return location;
}

void Shader::SetUniform(const char* id, const glm::mat4& value) {
	GLuint location = GetUniformLocation(id);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniform(const char* id, glm::vec4 value) {
	GLuint location = GetUniformLocation(id);
	glUniform4fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const char* id, glm::vec3 value) {
	GLuint location = GetUniformLocation(id);
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const char* id, glm::vec2 value) {
	GLuint location = GetUniformLocation(id);
	glUniform2fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const char* id, float value) {
	GLuint location = GetUniformLocation(id);
	glUniform1f(location, value);
}

void Shader::SetUniform(const char* id, int value) {
	GLuint location = GetUniformLocation(id);
	glUniform1i(location, value);
}

void Shader::SetUniform(const char* id, int texture_id, const Texture& texture) {
	GLuint location = GetUniformLocation(id);
	glActiveTexture(GL_TEXTURE0 + texture_id);
	glBindTexture(texture.GetTextureType(), texture.GetTextureObject());
	glUniform1i(location, texture_id);
}

} // namespace glsp

