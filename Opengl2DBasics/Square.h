#pragma once
#include "Object.h"

class Square : public Object {
	private:
		float verts[8];

		unsigned int indices[6];

		const int bufferSize = 8;

	public:
		Square(unsigned const& indices, float const& verts, glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);

		Square(Object const& object, Square const& square);

		int GetBufferSize();

		float* GetVertices();

		unsigned int* GetIndices();
};

