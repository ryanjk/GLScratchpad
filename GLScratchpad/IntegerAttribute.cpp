#include "IntegerAttribute.h"

namespace glsp {

IntegerAttribute::IntegerAttribute() : data_{} {}

IntegerAttribute::IntegerAttribute(int data) : data_(data) {}

IntegerAttribute::~IntegerAttribute() {}

void IntegerAttribute::Get(void* out) {
	int* out_int = static_cast<int*>(out);
	*out_int = data_;
}

void IntegerAttribute::Copy(glsp::ShaderAttribute* shader_attribute) {
	shader_attribute->Get(&data_);
}

} // namespace glsp