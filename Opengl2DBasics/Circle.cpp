#include "Circle.h"

Circle::Circle(const float& radius, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale) : 
Object(position, rotation, scale) {
	verticesNumber = sides + 2;
	indicesNumber = sides * 3;
	this->radius = radius;
	verts = new float[verticesNumber * VERTEX_BUFFER_SIZE];
	indices = new unsigned int[indicesNumber];
	verts[0] = 0;
	verts[1] = 0;
	Fill();
	GenBuffer();
}

Circle::Circle(const Circle& circle) : Object(circle) {
	verticesNumber = circle.verticesNumber;
	indicesNumber = circle.indicesNumber;
	radius = circle.radius;
	verts = new float[verticesNumber * VERTEX_BUFFER_SIZE];
	indices = new unsigned int[indicesNumber];
	verts[0] = 0;
	verts[1] = 0;
	Fill();
	GenBuffer();
}

Circle::~Circle() {
	delete vertexBuffer;
	delete indexBuffer;
	delete vao;
	delete layout;
}

void Circle::Fill() {
	double radians = 2 * 3.14159265359;
	float centerX = verts[0];
	float centerY = verts[1];
	for (int i = 1; i < verticesNumber; i++) {
		verts[i * 2] = centerX + (radius * glm::cos(i * radians / sides));
		verts[(i * 2) + 1] = centerY + (radius * glm::sin(i * radians / sides));
	}

	unsigned int b = 1, c = 2;
	// indices
	for (unsigned int i = 0; i < indicesNumber; i += 3)
	{
		c = b % sides + 1;
		indices[i] = 0;
		indices[i + 1] = b;
		indices[i + 2] = c;
		b++;
	}
}

void Circle::GenBuffer() {
	vao = new VertexArray();
	layout = new VertexBufferLayout();
	layout->Push<float>(VERTEX_BUFFER_SIZE);
	vertexBuffer = new VertexBuffer(verts, (verticesNumber * VERTEX_BUFFER_SIZE) * sizeof(float));
	vao->AddBuffer(*vertexBuffer, *layout);	
	indexBuffer = new IndexBuffer(indices, indicesNumber * sizeof(unsigned int));
}

void Circle::Bind() { vao->Bind(); }

void Circle::Draw(const unsigned int& uniform) { 
	GLCall(glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(transform)));
	GLCall(glDrawElements(GL_TRIANGLE_FAN, indicesNumber, GL_UNSIGNED_INT, nullptr) );
	
}