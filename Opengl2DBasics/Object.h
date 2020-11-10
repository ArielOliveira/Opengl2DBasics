#pragma once

#include <glm.hpp>
#include <ext.hpp>
#include <glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"

// Constantes para índices de attributos no vertex shader
const unsigned VERTEX_SHADER_POSITION = 0;

// Constantes para formato do buffer
const unsigned VERTEX_BUFFER_SIZE = 2; // usaremos apenas x e y para representar os vértices

class Object {
	protected:
		glm::mat4 transform;

		glm::mat4 position;
		glm::mat4 rotation;
		glm::mat4 scale;

		unsigned int verticesNumber;
		unsigned int indicesNumber;
	public:
		static int instances;

		Object(glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);

		Object(Object const& object);

		~Object();

		virtual void Translate(glm::vec3 const& translation);
		
		virtual void Rotate(glm::vec2 const& degrees, glm::vec3 const& direction);

		virtual void Scale(glm::vec3 const& _scale);

		glm::mat4 GetPosition();
		glm::mat4 GetRotation();
		glm::mat4 GetScale();

		const float& GetTransform();

		unsigned int GetVertsNumber() const { return verticesNumber * VERTEX_BUFFER_SIZE; }
		unsigned int GetIndexNumber() const { return indicesNumber; }

		virtual void Draw(const unsigned int& uniform) = 0;
};

