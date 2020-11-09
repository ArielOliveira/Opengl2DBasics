#pragma once
#include "Object.h"

class Square : public Object {
	private:
		float verts[8] = {
		-.5f, -.5f,
		 .5f, -.5f,
		 .5f,  .5f,
		-.5f,  .5f
		};

		unsigned indices[6] = {
			 0, 1, 2,
			 2, 3, 0
		};

		VertexArray* vao;
		VertexBufferLayout* layout;

		VertexBuffer* vertexBuffer;
		IndexBuffer* indexBuffer;

	public:
		Square(glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);
		Square(Square const& square);
		~Square();

		void GenBuffer();

		void Bind();
		void Draw(const unsigned int& uniform);
};

