#include "Square.h"

Square::Square(glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale) :
	Object(position, rotation, scale) {
	verticesNumber = 4;
	indicesNumber = 6;

	GenBuffer();
}

Square::Square(Square const& square) : Object(square) {
	verticesNumber = 4;
	indicesNumber = 6;

	GenBuffer();
}

Square::~Square() {
}

void Square::GenBuffer() {
	Object::GenBuffer();
	glEnableVertexAttribArray(VERTEX_SHADER_POSITION);
	vertexBuffer = new VertexBuffer(verts, (verticesNumber * VERTEX_BUFFER_SIZE) * sizeof(float));
	glVertexAttribPointer(VERTEX_SHADER_POSITION, VERTEX_BUFFER_SIZE, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	indexBuffer = new IndexBuffer(indices, indicesNumber * sizeof(unsigned int));
}

void Square::Draw(const unsigned int& uniform) { 
	GLCall(glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(transform)));
	GLCall(glDrawElements(GL_LINE_LOOP, indicesNumber, GL_UNSIGNED_INT, nullptr)); 
}
