#pragma once
#include "Object.h"

class Square : public Object {
	private:
		float verts[8];
		unsigned int indices[6];

		unsigned int vertexBuffer;
		unsigned int indexBuffer;

	public:
		Square(float const* verts, unsigned const* indices, glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);

		Square(Object const& object, Square const& square);

		float* GetVertexArray();
		unsigned int* GetIndexArray();

		const int GetVertexBufferSize();
		const int GetIndexBufferSize();
		
		virtual unsigned int* GetVertexPtr();
		virtual unsigned int* GetIndexPtr();
		virtual unsigned int GetVertexBufferID();
		virtual unsigned int GetIndexBufferID();

		
};

