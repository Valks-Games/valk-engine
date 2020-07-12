#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <string>
#include <iostream>

#include "graphics/Renderer.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Shader.h"
#include "window/Window.h"

int main(void)
{
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

		ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");

		GLuint shader = CreateShader(source.VertexSource, source.FragmentSource);
		GLCall(glUseProgram(shader));

		GLint location = glGetUniformLocation(shader, "u_Color");
		GLCall(glUniform4f(location, 1.0f, 0.0f, 0.5f, 1.0f));

		GLCall(glBindVertexArray(0));
		GLCall(glUseProgram(0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		float g = 0.0f;
		float increment = 0.01f;

		while (!window.Closed())
		{
			window.Clear();
			double x, y;
			window.getMousePos(x, y);
			std::cout << x << ", " << y << std::endl;

			GLCall(glUseProgram(shader));
			GLCall(glUniform4f(location, 0.0f, g, 0.0f, 1.0f));

			GLCall(glBindVertexArray(vao));
			ib.Bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			if (g > 1.0f)
				increment = -0.01f;
			else if (g < 0.0f)
				increment = 0.01f;

			g += increment;

			window.Update();
		}

		GLCall(glDeleteProgram(shader));
	}

	glfwTerminate();
	return 0;
}