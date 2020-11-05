#include "Square.h"

Square::Square(float const* verts, unsigned const* indices, glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale) :
	Object(transform, position, rotation, scale) {
	verticesNumber = 4;
	indicesNumber = 6;

	for (int i = 0; i < verticesNumber * VERTEX_BUFFER_SIZE; i++)
		this->verts[i] = verts[i];

	for (int i = 0; i < indicesNumber; i++)
		this->indices[i] = indices[i];

	GenBuffer();
}

Square::Square(Square const& square) : Object(square) {
	verticesNumber = 4;
	indicesNumber = 6;

	for (int i = 0; i < verticesNumber * VERTEX_BUFFER_SIZE; i++)
		this->verts[i] = square.verts[i];

	for (int i = 0; i < indicesNumber; i++)
		this->indices[i] = square.indices[i];

	GenBuffer();
}

void Square::GenBuffer() {
	Object::GenBuffer();
	glEnableVertexAttribArray(VERTEX_SHADER_POSITION);
	vertexBuffer = new VertexBuffer(verts, (verticesNumber * VERTEX_BUFFER_SIZE) * sizeof(float));
	glVertexAttribPointer(VERTEX_SHADER_POSITION, VERTEX_BUFFER_SIZE, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	indexBuffer = new IndexBuffer(indices, indicesNumber * sizeof(unsigned int));
}

float* Square::GetVertexArray() { return verts; }
unsigned int* Square::GetIndexArray() { return indices; }
