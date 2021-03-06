#include "Camera.h"

Camera::Camera(glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale) : 
	Object(position, rotation, scale) {
	startPos = position;
	startRot = rotation;
	startScale = scale;

	verticesNumber = 0;
	indicesNumber = 0;
}

Camera::Camera(Camera const& camera) : Object(camera) {
	startPos = camera.position;
	startRot = camera.rotation;
	startScale = camera.scale;

	verticesNumber = 0;
	indicesNumber = 0;
}

void Camera::GenBuffer() {}

void Camera::Draw(const unsigned int& uniform) { GLCall(glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(transform))); }

void Camera::Reset() {
	transform = startPos * startRot * startScale;
	position = startPos;
	rotation = startRot;
	scale = startScale;
}