#include "FloatAttribute.h"

#include "Util.h"

namespace glsp {

FloatAttribute::FloatAttribute() : data_{} {
	//PrintLine("FloatAttribute::FloatAttribute()");
}

FloatAttribute::FloatAttribute(float data) : data_(data) {
	//PrintLine(std::string("FloatAttribute::FloatAttribute(") + std::to_string(data) + ")");
}

FloatAttribute::~FloatAttribute() {
	//PrintLine("FloatAttribute::~FloatAttribute()");
}

void FloatAttribute::Get(void* out) {
	float* out_float = static_cast<float*>(out);
	*out_float = data_;
}

void FloatAttribute::Copy(glsp::ShaderAttribute* in) {
	in->Get(&data_);
}

}

