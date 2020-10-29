#pragma once

#include <glm.hpp>
#include <ext.hpp>

class Object {
	private:
		float *verts;

		glm::mat4 transform;

		glm::mat4 position;
		glm::mat4 rotation;
		glm::mat4 scale;

		unsigned buffer;

	public:
		static int instances;

		Object(float const& verts, glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);

		Object(Object const& object);

		~Object();

		float* GetVertices();

		void Translate(glm::vec3 const& translation);
		
		void Rotate(glm::vec2 const& degrees, glm::vec3 const& direction);

		void Scale(glm::vec3 const& _scale);

		glm::mat4 GetModel();
};

