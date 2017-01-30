#include "Application.h"

#include "TestShader.h"
#include "ScreenSpaceShader.h"
#include "TextureProjectionShader.h"
#include "DynamicSignedText.h"
//INSERT_HEADER_HERE

namespace glsp {

void Application::LoadProgram(std::string name) {
	if (name == "test") {
		program_ = std::make_shared<glsp::TestShader>(&camera_);
	}
	else if (name == "screen space") {
		program_ = std::make_shared<glsp::ScreenSpaceShader>(&camera_);
	}
	else if (name == "texture projection") {
		program_ = std::make_shared<glsp::TextureProjectionShader>(&camera_);
	}
	else if (name == "DynamicSignedText") {
		program_ = std::make_shared<glsp::DynamicSignedText>(&camera_);
	}
	//INSERT_STATEMENT_HERE
	program_->Init();
}

} // namespace glsp