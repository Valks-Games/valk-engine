#pragma once

#include <GL/glew.h>

namespace valk {
	namespace graphics {
		class VertexBuffer
		{
		private:
			GLuint m_RendererID;
		public:
			VertexBuffer(const void* data, GLuint size);
			~VertexBuffer();

			void bind() const;
			void unbind() const;
		};
	}
}
