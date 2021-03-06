#include "VertexArray.h"

VertexArray::VertexArray() { 
	GLCall(glGenVertexArrays(1, &rendererID));
}
VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &rendererID));
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(rendererID));
}

void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	unsigned int i = 0;
	for (const auto& element : elements) {
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(),
			(const void*)offset));
		offset += element.count;
		i++;
	}
}
