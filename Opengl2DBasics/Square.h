#pragma once
#include "Object.h"

class Square : public Object {
	private:
		float verts[8];
		unsigned int indices[6];
	public:
		Square(float const* verts, unsigned const* indices, glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);

		Square(Square const& square);

		void GenBuffer();

		float* GetVertexArray();
		unsigned int* GetIndexArray();	
};

