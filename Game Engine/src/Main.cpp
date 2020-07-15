#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "graphics\renderer.h"
#include "graphics\vertexbuffer.h"
#include "graphics\indexbuffer.h"
#include "graphics\shader.h"
#include "graphics\window.h"

#include "maths\maths.h"

int main(void)
{
	using namespace valk;
	using namespace graphics;
	using namespace maths;

	Window window("Game Engine", 640, 480);

	{
		GLfloat positions[] = {
			-0.5f, -0.5f, // 0
			 0.5f, -0.5f, // 1
			 0.5f,  0.5f, // 2
			-0.5f,  0.5f, // 3
		};

		GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLuint vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		VertexBuffer vb(positions, sizeof(positions));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

		IndexBuffer ib(indices, 6);

		ShaderProgramSource source = parseShader("res/shaders/Basic.shader");

		GLuint shader = createShader(source.VertexSource, source.FragmentSource);
		GLCall(glUseProgram(shader));

		GLint location = glGetUniformLocation(shader, "u_Color");
		GLCall(glUniform4f(location, 1.0f, 0.0f, 0.5f, 1.0f));

		GLCall(glBindVertexArray(0));
		GLCall(glUseProgram(0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		float g = 0.0f;
		float increment = 0.01f;

		vec4 a(0.2f, 0.3f, 0.8f, 1.0f);
		vec4 b(0.5f, 0.2f, 0.1f, 1.0f);

		vec4 c = a * b;

		while (!window.closed())
		{
			window.clear();

			std::cout << c << std::endl;

			GLCall(glUseProgram(shader));
			GLCall(glUniform4f(location, 0.0f, g, 0.0f, 1.0f));

			GLCall(glBindVertexArray(vao));
			ib.bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			if (g > 1.0f)
				increment = -0.01f;
			else if (g < 0.0f)
				increment = 0.01f;

			g += increment;

			window.update();
		}

		GLCall(glDeleteProgram(shader));
	}

	glfwTerminate();
	return 0;
}