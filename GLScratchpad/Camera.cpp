#include "Camera.h"

namespace glsp {

Camera::Camera() : transform_{}, inv_transform_{}, projection_{} {
}

Camera::~Camera() {
}

void Camera::SetTransform(const glm::mat4& transform) {
	transform_ = transform;
	inv_transform_ = glm::inverse(transform);
}

void Camera::SetProjection(const glm::mat4& projection) {
	projection_ = projection;
}

glm::mat4 Camera::Transform() const {
	return transform_;
}

glm::mat4 Camera::Projection() const {
	return projection_;
}

glm::mat4 Camera::View() const {
	return inv_transform_;
}

} // namespace glsp

