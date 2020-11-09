#include "Object.h"

Object::Object(glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale) {
	instances++;

	this->transform = position * rotation * scale;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;

	verticesNumber = 0;
	indicesNumber = 0;
}

Object::Object(Object const& object) {
	instances++;
	transform = object.transform;
	position = object.position;
	rotation = object.rotation;
	scale = object.scale;

	verticesNumber = object.verticesNumber;
	indicesNumber = object.indicesNumber;
}

Object::~Object() {
	instances--;
}

void Object::Translate(glm::vec3 const& translation) {
	glm::mat4 displacement = glm::translate(glm::mat4(1.f), translation);
	position = displacement * position;
	transform = displacement * transform;
}

void Object::Rotate(glm::vec2 const& degrees, glm::vec3 const& direction) {
	glm::mat4 rotationX = glm::rotate(position, degrees.y, direction);
	glm::mat4 rotationY = glm::rotate(rotationX, degrees.x, direction);
	rotation = rotationY;
	transform = rotation * transform;
}

void Object::Scale(glm::vec3 const& _scale) {
	glm::mat4 newScale = glm::scale(glm::mat4(1.f), _scale);
	scale = newScale * scale;
	transform = newScale * transform;
}

glm::mat4 Object::GetPosition() { return position; }
glm::mat4 Object::GetRotation() { return rotation; }
glm::mat4 Object::GetScale() { return scale; }
glm::mat4 Object::GetTransform() { return transform; }
