#ifndef GLSP_DynamicSignedText_H
#define GLSP_DynamicSignedText_H

#include <memory>

#include "AbstractShader.h"
#include "glsp_gl_util.h"

namespace glsp {

class DynamicSignedText : public AbstractShader {
public:
	DynamicSignedText(glsp::Camera* camera = nullptr);
	~DynamicSignedText();

	void Init() override;
	void Close() override;
	void Render(glsp::RenderData) override;

private:

};

} //namespace glsp

#endif
