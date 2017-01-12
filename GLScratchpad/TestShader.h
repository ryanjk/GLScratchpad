#ifndef GLSP_TEST_SHADER_H
#define GLSP_TEST_SHADER_H

#include <memory>

#include "AbstractShader.h"
#include "glsp_gl_util.h"

namespace glsp {

class TestShader : public AbstractShader {
public:
	TestShader(glsp::Camera* camera = nullptr);
	~TestShader();

	void Init() override;
	void Close() override;
	void Render(glsp::RenderData) override;

private:
	MESH(mesh, "monkey.obj");
	MESH(mesh2, "monkey.obj");
	TEXTURE(tex, "monkey_tex.png");
	TEXTURE(map_tex, "map.png");
	SHADER(shader, "BlinnPhong");
};

} //namespace glsp

#endif
