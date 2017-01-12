#ifndef GLSP_FLOAT_ATTRIBUTE_H
#define GLSP_FLOAT_ATTRIBUTE_H

#include "ShaderAttribute.h"

namespace glsp {

class FloatAttribute : public glsp::ShaderAttribute {
public:
	FloatAttribute();
	FloatAttribute(float);
	~FloatAttribute();

	void Get(void*) override;
	void Copy(glsp::ShaderAttribute*) override;

private:
	float data_;
};

} // namespace glsp


#endif