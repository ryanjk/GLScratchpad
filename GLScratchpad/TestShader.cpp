#include "TestShader.h"

#include <cmath>

#include "glm.hpp"
#include "glm\gtx\transform.hpp"
#include "glew.h"

namespace glsp {

TestShader::TestShader(glsp::Camera* camera) : AbstractShader(camera) {
}

TestShader::~TestShader() {
}

void TestShader::Init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
}

void TestShader::Close() {

}

void TestShader::Render(glsp::RenderData render_data) {
	const GLfloat color[] = { 0.0, 0.0, 0.0 };
	const GLfloat white[] = { 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	glClearBufferfv(GL_DEPTH, 0, white);

	mat4 model;

	GET_V3(t_scale);
	auto s = glm::scale(t_scale);

	GET_V3(t_position);
	auto t = glm::translate(t_position);

	GET_V3(t_rotation);
	auto xr = glm::rotate(glm::radians(t_rotation[0]), vec3(1.0f, 0.0f, 0.0f));
	auto yr = glm::rotate(glm::radians(t_rotation[1]), vec3(0.0f, 1.0f, 0.0f));
	auto zr = glm::rotate(glm::radians(t_rotation[2]), vec3(0.0f, 0.0f, 1.0f));
	auto r = yr * xr * zr;

	model = t * r * s * model;

	GET_F(diffuse_intensity);
	GET_F(specular_intensity);
	GET_F(ambient_intensity);

	GET_V3(light_pos);

	shader->Use();
	shader->SetUniform("m", model);
	shader->SetUniform("v", Camera()->View());
	shader->SetUniform("p", Camera()->Projection());
	shader->SetUniform("diffuse_map", 0, *tex);
	shader->SetUniform("diffuse_i", diffuse_intensity);
	shader->SetUniform("specular_i", (float) pow(10, specular_intensity));
	shader->SetUniform("ambient_i", ambient_intensity);
	shader->SetUniform("light_pos", light_pos);
	shader->SetUniform("view", glm::normalize(Camera()->Transform()[2]));

	mesh->Draw();

}

} //namespace glsp

