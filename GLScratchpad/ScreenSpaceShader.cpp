#include "ScreenSpaceShader.h"

#include "glm\gtx\transform.hpp"
#include "Util.h"

namespace glsp {

ScreenSpaceShader::ScreenSpaceShader(glsp::Camera* camera) : AbstractShader(camera) {
}


ScreenSpaceShader::~ScreenSpaceShader() {
}

void ScreenSpaceShader::Init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);

	glGenTextures(1, &_color_tex);
	glBindTexture(GL_TEXTURE_2D, _color_tex);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 512, 512);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &_depth_buffer);
	glBindTexture(GL_TEXTURE_2D, _depth_buffer);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, 512, 512);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _color_tex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depth_buffer, 0);

	static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, draw_buffers);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		PrintLine("" + status);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ScreenSpaceShader::Close() {}

void ScreenSpaceShader::Render(RenderData rd) {

	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	const GLfloat white[3] = {1.0f, 1.0f, 1.0f};
	const GLfloat black[3] = { 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, white);

	gray_shader->Use();

	GET_F(shade);
	gray_shader->SetUniform("shade", shade);

	GET_V3(light_pos);
	gray_shader->SetUniform("light_pos", light_pos);

	GET_F(z);
	auto scene_pos = vec3(0.0f, 0.0f, z);

	GET_F(pitch);
	auto scene_rot = glm::rotate(glm::radians(pitch), vec3(1.0f, 0.0f, 0.0f));

	auto world_transform = glm::translate(scene_pos) * scene_rot;
	gray_shader->SetUniform("m", world_transform);

	gray_shader->SetUniform("v", Camera()->View());
	gray_shader->SetUniform("p", Camera()->Projection());

	monkey_scene->Draw();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace glsp

