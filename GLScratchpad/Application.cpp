#include "Application.h"

#include <math.h>

#include <iostream>

#include "glm\gtc\matrix_transform.hpp"

#include "glew.h"

#include "AbstractShader.h"
#include "ShaderAttribute.h"

namespace glsp {

Application::Application() : camera_{}, program_{} {
	auto projection = glm::perspective(glm::radians(60.0f), 1.2f, 0.001f, 1000.0f);
	camera_.SetProjection(projection);
}

Application::~Application() {
}

void Application::CloseProgram() {
	program_->Close();
	program_ = nullptr;
}

void Application::InsertProgramAttribute(std::string id, glsp::ShaderAttribute* attribute) {
	program_->InsertAttribute(id, attribute);
}

void Application::SetProgramAttribute(std::string id, glsp::ShaderAttribute* attribute) {
	program_->SetAttribute(id, attribute);
}

void Application::Resize(int width, int height) {
	glViewport(0, 0, width, height);
	auto projection = glm::perspective(45.0f, ((float)width)/height, 0.001f, 1000.0f);
	camera_.SetProjection(projection);
}

void Application::Draw(glsp::RenderData render_data) {
	if (program_.get() != nullptr) {
		program_->Draw(render_data);
	}
	else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

} // namespace glsp
