#ifndef GLSP_SHADER_ATTRIBUTE_H
#define GLSP_SHADER_ATTRIBUTE_H

namespace glsp {

class ShaderAttribute {
public:
	ShaderAttribute() {}
	virtual ~ShaderAttribute() {}

	virtual void Get(void*) = 0;
	virtual void Copy(ShaderAttribute*) = 0;
	virtual void Init() {}
};

} //namespace glsp


#endif

