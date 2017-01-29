#pragma once
#include "AbstractShader.h"
#include "glsp_gl_util.h"

#include "TextureLoadData.h"

namespace glsp {
class TextureProjectionShader : public AbstractShader {
public:
	TextureProjectionShader(glsp::Camera* camera = nullptr);
	~TextureProjectionShader();

	void Init() override;
	void Close() override;
	void Render(glsp::RenderData) override;

private:
	SHADER(tp, "TextureProjection");
	MESH(monkey_scene, "monkey_scene.obj");
	const TextureLoadData load_data = { GL_TEXTURE_2D, true, GL_LINEAR, GL_CLAMP_TO_BORDER };
	TEXTURE_CUSTOM(tex, load_data, "monkey_tex.png");
};
} // namespace glsp


