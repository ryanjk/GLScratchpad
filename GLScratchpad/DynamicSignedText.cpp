#include "DynamicSignedText.h"

#include <cmath>

#include "glm.hpp"
#include "glm\gtx\transform.hpp"
#include "glew.h"

namespace glsp {

DynamicSignedText::DynamicSignedText(glsp::Camera* camera) : AbstractShader(camera) {
}

DynamicSignedText::~DynamicSignedText() {
}

void DynamicSignedText::Init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
}

void DynamicSignedText::Close() {

}

void DynamicSignedText::Render(glsp::RenderData render_data) {
	const GLfloat color[] = { 0.0, 0.0, 0.0 };
	const GLfloat white[] = { 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	glClearBufferfv(GL_DEPTH, 0, white);



}

} //namespace glsp

