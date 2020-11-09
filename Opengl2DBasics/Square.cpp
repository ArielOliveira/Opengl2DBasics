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
	delete vertexBuffer;
	delete indexBuffer;
	delete vao;
	delete layout;
}

void Square::GenBuffer() {
	vao = new VertexArray();
	layout = new VertexBufferLayout();
	layout->Push<float>(VERTEX_BUFFER_SIZE);
	vertexBuffer = new VertexBuffer(verts, (verticesNumber * VERTEX_BUFFER_SIZE) * sizeof(float));
	vao->AddBuffer(*vertexBuffer, *layout);
	indexBuffer = new IndexBuffer(indices, indicesNumber * sizeof(unsigned int));
}

void Square::Bind() { vao->Bind(); }

void Square::Draw(const unsigned int& uniform) { 
	GLCall(glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(transform)));
	GLCall(glDrawElements(GL_LINE_LOOP, indicesNumber, GL_UNSIGNED_INT, nullptr)); 
}
