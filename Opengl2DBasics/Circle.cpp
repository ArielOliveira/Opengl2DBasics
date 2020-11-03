#include "Circle.h"

Circle::Circle(const float& radius, glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale) : 
Object(transform, position, rotation, scale) {
	this->radius = radius;
	vertices = new float[sides * 2];
	Fill();
}

void Circle::Fill() {
	
}
