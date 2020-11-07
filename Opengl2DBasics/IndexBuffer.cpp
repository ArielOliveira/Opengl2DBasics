#include "IndexBuffer.h"

#include <iostream>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) {
    this->count = count;

    glGenBuffers(1, &rendererID); // Gera um objeto de buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID); // Determina o tipo do objeto de buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); // Determina o tipo, tamanho, ponteiro e padrao de armazenamento respectivamente
}
IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &rendererID); }

void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID); }
void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

unsigned int IndexBuffer::GetCount() const { return count; }