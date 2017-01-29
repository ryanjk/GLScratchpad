#include "TextureProjectionShader.h"

#include "glm\gtx\transform.hpp"
#include "glm\gtx\projection.hpp"

namespace glsp {

TextureProjectionShader::TextureProjectionShader(glsp::Camera* camera) : AbstractShader(camera) {}


TextureProjectionShader::~TextureProjectionShader()
{
}

void TextureProjectionShader::Init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void TextureProjectionShader::Close() {

}

void TextureProjectionShader::Render(glsp::RenderData) {
	const GLfloat color[] = { 0.0, 0.0, 0.0 };
	const GLfloat white[] = { 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	glClearBufferfv(GL_DEPTH, 0, white);

	tp->Use();

	GET_F(shade);
	tp->SetUniform("shade", shade);

	GET_V3(light_pos);
	tp->SetUniform("light_pos", light_pos);

	GET_F(z);
	auto scene_pos = vec3(0.0f, 0.0f, z);

	GET_F(pitch);
	auto scene_rot = glm::rotate(glm::radians(pitch), vec3(1.0f, 0.0f, 0.0f));
	auto world_transform = glm::translate(scene_pos) * scene_rot;
	tp->SetUniform("m", world_transform);
	tp->SetUniform("v", Camera()->View());
	tp->SetUniform("p", Camera()->Projection());

	GET_V3(tex_position);
	GET_V3(tex_rotation);
	GET_V3(tex_scale);
	mat4 tex_transform = 
		glm::scale(tex_scale)
		* glm::rotate(glm::radians(tex_rotation.x), vec3(1.0f, 0.0f, 0.0f))
		* glm::rotate(glm::radians(tex_rotation.y), vec3(0.0f, 1.0f, 0.0f))
		* glm::rotate(glm::radians(tex_rotation.z), vec3(0.0f, 0.0f, 1.0f))
		* glm::translate(tex_position);

	GET_F(fov);
	GET_F(far);
	mat4 tex_proj = glm::perspective(glm::radians(fov), 1.0f, 0.01f, far);
	mat4 bias = glm::scale(vec3(0.5f, 0.5f, 0.5f)) * glm::translate(vec3(1.0f, 1.0f, 1.0f));

	tp->SetUniform("tex_v", glm::inverse(tex_transform));
	tp->SetUniform("tex_p", tex_proj);
	tp->SetUniform("bias", bias);

	tp->SetUniform("proj_texture", 0, *tex);

	monkey_scene->Draw();
}

} // namespace glsp