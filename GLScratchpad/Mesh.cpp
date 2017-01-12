#include "Mesh.h"

#include <algorithm>
#include <chrono>

#include "tiny_obj_loader.h"
#include "Util.h"
#include "directories.h"

namespace glsp {

Mesh::Mesh(const std::string& filename) : filename_(filename) {
	std::string inputfile = resource_dir + "Mesh\\" + filename;
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

	if (!err.empty()) { // `err` may contain warning message.
		PrintLine(err);
	}

	if (!ret) {
		exit(1);
	}

	std::vector<glm::vec3> vertices;
	vertices.reserve(shapes[0].mesh.indices.size());
	std::vector<glm::vec3> normals;
	normals.reserve(shapes[0].mesh.indices.size());
	std::vector<glm::vec2> uvs;
	uvs.reserve(shapes[0].mesh.indices.size());

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

				float vx = attrib.vertices[3 * idx.vertex_index + 0];
				float vy = attrib.vertices[3 * idx.vertex_index + 1];
				float vz = attrib.vertices[3 * idx.vertex_index + 2];
				vertices.emplace_back(vx, vy, vz );

				float nx = attrib.normals[3 * idx.normal_index + 0];
				float ny = attrib.normals[3 * idx.normal_index + 1];
				float nz = attrib.normals[3 * idx.normal_index + 2];
				normals.emplace_back(nx, ny, nz);

				if (!attrib.texcoords.empty()) {
					float tx = attrib.texcoords[2 * idx.texcoord_index + 0];
					float ty = attrib.texcoords[2 * idx.texcoord_index + 1];
					uvs.emplace_back(tx, ty);
				}
			}
			index_offset += fv;

			// per-face material
			//shapes[s].mesh.material_ids[f];
		}
	}

	num_verts_ = vertices.size();

	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &position_vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &normals_vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * normals.size(), normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	if (!uvs.empty()) {
		glGenBuffers(1, &uv_vbo_);
		glBindBuffer(GL_ARRAY_BUFFER, uv_vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * uvs.size(), uvs.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &uv_vbo_);
	glDeleteBuffers(1, &normals_vbo_);
	glDeleteBuffers(1, &position_vbo_);
	glDeleteVertexArrays(1, &vao_);
}

void Mesh::LoadData() {

}

void Mesh::Draw() const {
	glBindVertexArray(vao_);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLES, 0, num_verts_);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindVertexArray(0);
}

GLuint Mesh::GetVAO() const {
	return vao_;
}

GLuint Mesh::GetPositionVBO() const {
	return position_vbo_;
}

GLuint Mesh::GetNormalVBO() const {
	return normals_vbo_;
}

unsigned int Mesh::GetNumVerts() const {
	return num_verts_;
}

} // namespace glsp
