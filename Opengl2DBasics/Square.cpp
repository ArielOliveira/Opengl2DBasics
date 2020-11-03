#include "Square.h"

Square::Square(float const* verts, unsigned const* indices, glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale) :
	Object(transform, position, rotation, scale) {
	for (int i = 0; i < GetVertexBufferSize(); i++)
		this->verts[i] = verts[i];

	for (int i = 0; i < GetIndexBufferSize(); i++)
		this->indices[i] = indices[i];
}

Square::Square(Object const& object, Square const& square) : Object(object) {
	*verts = *square.verts;
	*indices = *square.indices;
}

float* Square::GetVertexArray() { return verts; }
unsigned int* Square::GetIndexArray() { return indices; }

const unsigned int Square::GetVertexBufferSize() { return 8 * sizeof(float); }
const unsigned int Square::GetIndexBufferSize() { return 6 * sizeof(unsigned int); }
unsigned int* Square::GetVertexPtr() { return &vertexBuffer; }
unsigned int* Square::GetIndexPtr() { return &indexBuffer; }
unsigned int Square::GetVertexBufferID() { return vertexBuffer; }
unsigned int Square::GetIndexBufferID() { return indexBuffer; }
