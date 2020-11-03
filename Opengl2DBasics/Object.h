#pragma once

#include <glm.hpp>
#include <ext.hpp>

class Object {
	private:
		glm::mat4 transform;

		glm::mat4 position;
		glm::mat4 rotation;
		glm::mat4 scale;
	public:
		static int instances;

		Object(glm::mat4 const& transform, glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);

		Object(Object const& object);

		~Object();

		void Translate(glm::vec3 const& translation);
		
		void Rotate(glm::vec2 const& degrees, glm::vec3 const& direction);

		void Scale(glm::vec3 const& _scale);

		glm::mat4 GetTransform();

		virtual float* GetVertexArray() = 0;
		virtual unsigned int* GetIndexArray() = 0;

		virtual const unsigned int GetVertexBufferSize() = 0;
		virtual const unsigned int GetIndexBufferSize() = 0;
		virtual unsigned int* GetVertexPtr() = 0;
		virtual unsigned int* GetIndexPtr() = 0;
		virtual unsigned int GetVertexBufferID() = 0;
		virtual unsigned int GetIndexBufferID() = 0;
};

