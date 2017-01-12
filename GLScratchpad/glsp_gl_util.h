#ifndef GLSP_GL_UTIL_H
#define GLSP_GL_UTIL_H

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

#define MESH(x,filename) std::shared_ptr<glsp::Mesh> x = std::make_shared<glsp::Mesh>(filename); 
#define TEXTURE(x,filename) std::shared_ptr<glsp::Texture> x = std::make_shared<glsp::Texture>(filename); 
#define SHADER(x,shader_name) std::shared_ptr<glsp::Shader> x = std::make_shared<glsp::Shader>(shader_name);

#endif