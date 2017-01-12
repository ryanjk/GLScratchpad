#ifndef GLSP_INT_ATTRIBUTE_H
#define GLSP_INT_ATTRIBUTE_H

#include "ShaderAttribute.h"

namespace glsp {

class IntegerAttribute : public ShaderAttribute {
public:
	IntegerAttribute();
	IntegerAttribute(int);
	~IntegerAttribute();

	void Get(void*) override;
	void Copy(glsp::ShaderAttribute*) override;

private:
	int data_;
};

} // namespace glsp

#endif