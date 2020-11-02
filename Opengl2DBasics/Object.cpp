#include "Object.h"

Object::Object(glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale) {
	instances++;
	this->transform = transform;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Object::Object(Object const& object) {
	instances++;
	transform = object.transform;
	position = object.position;
	rotation = object.rotation;
	scale = object.scale;
}

Object::~Object() {
	instances--;
}

void Object::Translate(glm::vec3 const& translation) {
	position = glm::translate(glm::mat4(1.f), translation);
	transform = transform * position;
}

void Object::Rotate(glm::vec2 const& degrees, glm::vec3 const& direction) {
	glm::mat4 rotationX = glm::rotate(position, degrees.y, direction);
	glm::mat4 rotationY = glm::rotate(rotationX, degrees.x, direction);
	rotation = rotationY;
	transform = transform * rotation;
}

void Object::Scale(glm::vec3 const& _scale) {
	scale = glm::scale(glm::mat4(1.f), _scale);
	transform = transform * scale;
}

glm::mat4 Object::GetTransform() { return transform; }
