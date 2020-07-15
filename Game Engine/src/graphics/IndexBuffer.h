#pragma once

#include <GL/glew.h>

namespace valk {
	namespace graphics {
		class IndexBuffer
		{
		private:
			GLuint m_RendererID;
			GLuint m_Count;
		public:
			IndexBuffer(const GLuint* data, GLuint count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return m_Count; }
		};
	}
}
