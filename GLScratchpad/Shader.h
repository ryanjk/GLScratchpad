#ifndef GLSP_SHADER_H
#define GLSP_SHADER_H

#include <string>
#include <fstream>
#include <vector>
#include <map>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glew.h>

namespace glsp {

class Texture;

enum class ShaderType {
	VERTEX, GEOMETRY, TESSELLATION, FRAGMENT
};

class Shader {
public:
	Shader(const std::string& shader_name);
	~Shader();

	void Use() const;

	void SetUniform(const char* id, const glm::mat4& value);
	void SetUniform(const char* id, glm::vec4 value);
	void SetUniform(const char* id, glm::vec3 value);
	void SetUniform(const char* id, glm::vec2 value);
	void SetUniform(const char* id, float value);
	void SetUniform(const char* id, int value);
	void SetUniform(const char* id, int texture_id, const Texture& texture);

	GLuint GetProgram() const;
private:
	void Load();
	GLuint LoadShader(ShaderType type);
	GLuint GetUniformLocation(const char* id);

	std::string shader_name_;
	GLuint program_;
	
};
} // namespace glsp
#endif