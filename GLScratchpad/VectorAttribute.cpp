#include "VectorAttribute.h"

namespace glsp {

VectorAttribute::VectorAttribute(const vec_attribute_t& vec) {
	data_ = vec;
}

VectorAttribute::~VectorAttribute() {
}

void VectorAttribute::Get(void* out) {
	auto size = data_.size();
	if (size == 2) {
		auto* vec_out = static_cast<glm::vec2*>(out);
		*vec_out = glm::vec2(data_[0], data_[1]);
	}
	else if (size == 3) {
		auto* vec_out = static_cast<glm::vec3*>(out);
		*vec_out = glm::vec3(data_[0], data_[1], data_[2]);
	}
	else if (size == 4) {
		auto* vec_out = static_cast<glm::vec4*>(out);
		*vec_out = glm::vec4(data_[0], data_[1], data_[2], data_[3]);
	}
}

void VectorAttribute::Copy(ShaderAttribute* shader_attribute) {
	auto size = data_.size();
	if (size == 2) {
		glm::vec2 new_data;
		shader_attribute->Get(&new_data);
		data_[0] = new_data[0];
		data_[1] = new_data[1];
	}
	else if (size == 3) {
		glm::vec3 new_data;
		shader_attribute->Get(&new_data);
		data_[0] = new_data[0];
		data_[1] = new_data[1];
		data_[2] = new_data[2];
	}
	else if (size == 4) {
		glm::vec4 new_data;
		shader_attribute->Get(&new_data);
		data_[0] = new_data[0];
		data_[1] = new_data[1];
		data_[2] = new_data[2];
		data_[3] = new_data[3];
	}
}

} // namespace glsp