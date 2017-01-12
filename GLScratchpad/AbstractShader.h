#ifndef GLSP_ABSTRACT_SHADER_H
#define GLSP_ABSTRACT_SHADER_H

#include <unordered_map>
#include <string>
#include <memory>

#include "ShaderAttribute.h"
#include "RenderData.h"
#include "Camera.h"
#include "glsp_types.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

#define GET(x) Get(#x, &x)
#define GET_F(x) float x; GET(x) 
#define GET_I(x) int x; GET(x) 
#define GET_V2(x) vec2 x; GET(x) 
#define GET_V3(x) vec3 x; GET(x) 
#define GET_V4(x) vec4 x; GET(x) 

namespace glsp {

class AbstractShader {
public:
	AbstractShader(glsp::Camera* camera = nullptr);
	virtual ~AbstractShader();

	void InsertAttribute(glsp::AttributeKey, glsp::ShaderAttribute*);
	void SetAttribute(glsp::AttributeKey, glsp::ShaderAttribute*);

	virtual void Init() = 0;
	virtual void Close() = 0;
	void Draw(glsp::RenderData);

protected:
	virtual void Render(glsp::RenderData) = 0;
	float Time();
	const glsp::Camera* Camera();

	void Get(glsp::AttributeKey, void*);

private:
	float time_;
	glsp::Camera* camera_;
	std::unordered_map<glsp::AttributeKey, std::shared_ptr<glsp::ShaderAttribute>> attributes_;
};

} //namespace glsp


#endif

