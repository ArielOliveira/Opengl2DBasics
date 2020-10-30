#include "Square.h"

Square::Square(float const& verts, glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale) :
	Object(verts, transform, position, rotation, scale) {
	*this->verts = verts;
}

Square::Square(Object const& object, Square const& square) : Object(object) {
	*verts = *square.verts;
}

int Square::GetBufferSize() { return bufferSize; }

float Square::GetVertices() { return *verts; }
