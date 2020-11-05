#pragma once
#include "Object.h"
class Circle : public Object {
	private:
		float radius;
		const int sides = 64;

		float* verts;
		unsigned int* indices;

		void Fill();
		void GenBuffer();
	public:
		Circle(const float& radius, glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);
		Circle(const Circle& circle);

		float* GetVertexArray();
		unsigned int* GetIndexArray();
};

