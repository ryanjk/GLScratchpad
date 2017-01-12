#ifndef GLSP_TEXTURELOADDATA_H
#define GLSP_TEXTURELOADDATA_H

#include <glew.h>

namespace glsp {
struct TextureLoadData {
	GLenum gl_type;
	bool use_mipmaps;
	GLenum filter;
	GLenum wrap;
};
} // namespace glsp


#endif