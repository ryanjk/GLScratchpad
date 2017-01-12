#ifndef GLSP_APPLICATION
#define GLSP_APPLICATION

#include <memory>
#include <string>

#include "RenderData.h"
#include "Camera.h"

namespace glsp {

class AbstractShader;
class ShaderAttribute;

class Application {
public:
	Application();
	~Application();

	void LoadProgram(std::string);
	void CloseProgram();

	void InsertProgramAttribute(std::string, glsp::ShaderAttribute*);
	void SetProgramAttribute(std::string, glsp::ShaderAttribute*);

	void Resize(int, int);
	void Draw(glsp::RenderData);

private:
	glsp::Camera camera_;
	std::shared_ptr<glsp::AbstractShader> program_;
};

} // namespace glsp

#endif
