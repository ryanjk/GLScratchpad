#include "Texture.h"

#include <qdebug.h>

#include "lodepng.h"
#include <vector>
#include <algorithm>
#include <chrono>

#include "Util.h"
#include "directories.h"

namespace {
	void SwapRows(std::vector<GLubyte>& pixels, unsigned int width, unsigned int r1, unsigned int r2) {
		auto row_width = width * 4;
		std::swap_ranges(pixels.begin() + row_width * r1, pixels.begin() + row_width * r1 + row_width,
			pixels.begin() + row_width * r2);
	}

	void FlipImage(std::vector<GLubyte>& pixels, unsigned int width, unsigned int height) {
		auto flips = height % 2 == 0 ? height / 2 : (height - 1) / 2;
		for (unsigned int i = 0; i < flips; ++i) {
			SwapRows(pixels, width, i, height - 1 - i);
		}
	}
} // namespace

namespace glsp {

Texture::Texture(const std::string& filename, const TextureLoadData& load_data) {
	PrintLine("creating texture with regular constructor");
	Load(filename, load_data);
}

Texture::Texture(Texture&& texture) : tex_object_(texture.tex_object_), type_(texture.type_) {
	PrintLine("create texture with copy constructor");
}

Texture::~Texture() {
	PrintLine("deleting texture " + tex_object_);
	glDeleteTextures(1, &tex_object_);
}

Texture& Texture::operator=(Texture&& texture) {
	PrintLine("copying texture with =");
	this->tex_object_ = texture.tex_object_;
	this->type_ = type_;
	return *this;
}

void Texture::Load(const std::string& filename, const TextureLoadData& load_data) {
	PrintLine("Texture::Load: Loading texture " + filename);
	type_ = load_data.gl_type;
	const std::string TEXTURE_DIRECTORY = resource_dir + "Texture\\";
	if (type_ == GL_TEXTURE_2D) {
		auto path = TEXTURE_DIRECTORY + filename;
		std::vector<GLubyte> pixels;
		unsigned int width, height;

		auto success = lodepng::decode(pixels, width, height, path);
		if (success != 0) {
			PrintLine("Texture::Load: lodepng: Couldn't load file " + filename);
			return;
		}

		auto t1 = std::chrono::high_resolution_clock::now();
		FlipImage(pixels, width, height);
		auto taken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count();
		PrintLine(std::string(" - Taken to flip (ms): ") + std::to_string(taken));

		static const GLfloat border_color[3] = { 1.0, 1.0, 1.0 };
		GLint wrap = load_data.wrap;

		GLint mag_filter = load_data.filter;
		GLint min_filter = load_data.filter;
		int mipmap_levels = 1;
		if (load_data.use_mipmaps) {
			if (load_data.filter == GL_LINEAR) {
				min_filter = GL_LINEAR_MIPMAP_LINEAR;
			}
			else if (load_data.filter == GL_NEAREST) {
				min_filter = GL_NEAREST_MIPMAP_NEAREST;
			}

			int log_2_size = static_cast<int>(log2(width));
			mipmap_levels = log_2_size + 1;
		}

		t1 = std::chrono::high_resolution_clock::now();
		glGenTextures(1, &tex_object_);
		glBindTexture(type_, tex_object_);
		glTexStorage2D(type_, mipmap_levels, GL_RGBA8, width, height);
		glTexSubImage2D(type_, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
		if (load_data.use_mipmaps) {
			glGenerateMipmap(type_);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
		
		if (wrap == GL_CLAMP_TO_BORDER) {
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
		}

		glBindTexture(type_, 0);
		taken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count();
		PrintLine(std::string(" - Taken to create GL object (ms): ") + std::to_string(taken));
	}
	else {
		PrintLine("Texture::Load: Type not supported");
	}

	PrintLine(" - Texture::Load: Done loading texture.");
}

GLuint Texture::GetTextureObject() const {
	return tex_object_;
}

GLenum Texture::GetTextureType() const {
	return type_;
}

} // namespace glsp