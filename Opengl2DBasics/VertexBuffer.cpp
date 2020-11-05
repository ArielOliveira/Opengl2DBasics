#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    glGenBuffers(1, &rendererID); // Gera um objeto de buffer
    glBindBuffer(GL_ARRAY_BUFFER, rendererID); // Determina o tipo do objeto de buffer
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // Determina o tipo, tamanho, ponteiro e padrao de armazenamento respectivamente
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &rendererID); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, rendererID); }
void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
