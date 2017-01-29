#ifndef GLSP_SCREEN_SPACE_SHADER_H
#define GLSP_SCREEN_SPACE_SHADER_H

#include "AbstractShader.h"
#include "glsp_gl_util.h"

namespace glsp {

class ScreenSpaceShader : public AbstractShader
{
public:
	ScreenSpaceShader(glsp::Camera*);
	~ScreenSpaceShader();

	void Init() override;
	void Close() override;
	void Render(glsp::RenderData) override;

private:
	MESH(monkey_scene, "monkey_scene.obj");
	SHADER(gray_shader, "Gray");

	GLuint _fbo;
	GLuint _color_tex;
	GLuint _depth_buffer;
};

} // namespace glsp

#endif
