#pragma once

#include <glew.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "OpenglDebugger.h"


class VertexArray {
	private:	
		unsigned int rendererID;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;
};

