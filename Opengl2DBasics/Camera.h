#pragma once
#include "Object.h"
using glm::mat4;
class Camera : public Object {
	private:
		mat4 startPos;
		mat4 startRot;
		mat4 startScale;

		void GenBuffer();
	public:
		Camera(glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);
		Camera(Camera const& camera);

		void Draw(const unsigned int& uniform);

		void Reset();

};
