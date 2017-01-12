#ifndef GLSP_VECTOR_ATTRIBUTE_H
#define GLSP_VECTOR_ATTRIBUTE_H

#include "ShaderAttribute.h"

#include <vector>

#include "glm.hpp"

using vec_attribute_t = std::vector<float>;

namespace glsp {

class VectorAttribute : public ShaderAttribute
{
public:
	VectorAttribute(const vec_attribute_t&);
	~VectorAttribute();

	void Get(void*) override;
	void Copy(ShaderAttribute*) override;

private:
	vec_attribute_t data_;
};

} // namespace glsp
#endif