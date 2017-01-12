#ifndef GLSP_CAMERA_H
#define GLSP_CAMERA_H

#include "glm.hpp"

namespace glsp {

class Camera {
public:
	Camera();
	~Camera();

	void SetTransform(const glm::mat4& transform);
	void SetProjection(const glm::mat4& projection);

	glm::mat4 Transform() const;
	glm::mat4 Projection() const;
	glm::mat4 View() const;

private:
	glm::mat4 transform_;
	glm::mat4 inv_transform_;
	glm::mat4 projection_;
};

} // namespace glsp

#endif