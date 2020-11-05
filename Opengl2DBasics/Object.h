#pragma once

#include <glm.hpp>
#include <ext.hpp>
#include <glew.h>

#include "CompiladorShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Object {
	protected:
		glm::mat4 transform;

		glm::mat4 position;
		glm::mat4 rotation;
		glm::mat4 scale;

		unsigned int vao;

		unsigned int verticesNumber;
		unsigned int indicesNumber;

		VertexBuffer *vertexBuffer;
		IndexBuffer *indexBuffer;

		virtual void GenBuffer();
	public:
		static int instances;

		Object(glm::mat4 const& position, glm::mat4 const& rotation, glm::mat4 const& scale);

		Object(Object const& object);

		~Object();

		void Bind();

		virtual void Translate(glm::vec3 const& translation);
		
		virtual void Rotate(glm::vec2 const& degrees, glm::vec3 const& direction);

		virtual void Scale(glm::vec3 const& _scale);

		glm::mat4 GetTransform();

		unsigned int GetVertsNumber() const { return verticesNumber * VERTEX_BUFFER_SIZE; }
		unsigned int GetIndexNumber() const { return indicesNumber; }

		virtual void Draw(const unsigned int& uniform) = 0;
};

