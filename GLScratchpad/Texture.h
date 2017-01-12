#pragma once
#include <glew.h>
#include <string>
#include "TextureLoadData.h"

namespace glsp {
enum class TextureAttribute {
	MIN_FILTER, MAG_FILTER, WRAP
};

class Texture {
public:
	Texture() = delete;
	Texture(const std::string& filename, const TextureLoadData& load_data = { GL_TEXTURE_2D, true, GL_LINEAR, GL_REPEAT });
	Texture(Texture&& texture);
	~Texture();	

	Texture& operator=(Texture&& texture);

	GLuint GetTextureObject() const;
	GLenum GetTextureType() const;

private:
	void Load(const std::string& filename, const TextureLoadData& load_data);
	GLuint tex_object_;
	GLenum type_;
};
} // namespace glsp
