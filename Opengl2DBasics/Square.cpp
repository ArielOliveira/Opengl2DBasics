#include "Square.h"

Square::Square(unsigned const& indices, float const& verts, glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale) :
	Object(verts, transform, position, rotation, scale) {
	*this->verts = verts;
	*this->indices = indices;
}

Square::Square(Object const& object, Square const& square) : Object(object) {
	*verts = *square.verts;
	*indices = *square.indices;
}

int Square::GetBufferSize() { return bufferSize; }

float* Square::GetVertices() { float *vertice = &verts[0]; return vertice; }

unsigned int* Square::GetIndices() { return &indices[0]; }
