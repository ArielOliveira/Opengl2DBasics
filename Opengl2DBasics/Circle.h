#pragma once
#include "Object.h"
class Circle : public Object {
	private:
		float radius;
		const int sides = 24;

		float* vertices;
		unsigned int* indices;

		void Fill();
		
	public:
		Circle(const float& radius, glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);
};

