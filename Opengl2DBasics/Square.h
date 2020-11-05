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
	public:
		Square(glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);

		Square(Square const& square);

		void GenBuffer();

		void Draw(const unsigned int& uniform);
};

