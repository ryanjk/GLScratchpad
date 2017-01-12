#ifndef GLSP_MESH_H
#define GLSP_MESH_H

#include <vector>
#include <string>

#include <glm\glm.hpp>
#include <glew.h>

namespace glsp {

class Mesh {
public:
	Mesh() = delete;
	Mesh(const std::string& filename);
	~Mesh();	

	GLuint GetVAO() const;
	GLuint GetPositionVBO() const;
	GLuint GetNormalVBO() const;
	
	unsigned int GetNumVerts() const;

	void Draw() const;

private:
	void LoadData();

	GLuint vao_;
	GLuint position_vbo_;
	GLuint normals_vbo_;
	GLuint uv_vbo_;

	unsigned int num_verts_;
	std::string filename_;
};
} // namespace glsp
#endif