#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "graphics\renderer.h"
#include "graphics\shader.h"
#include "graphics\window.h"

#include "graphics\buffers\buffer.h"
#include "graphics\buffers\indexbuffer.h"
#include "graphics\buffers\vertexarray.h"

#include "utils\fileutils.h"

#include "maths\maths.h"

#include "graphics/renderer2d.h"
#include "graphics/simple2drenderer.h"

int main()
{
	using namespace valk;
	using namespace graphics;
	using namespace maths;

	Window window("Game Engine", 1280, 720);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	Renderable2D sprite(maths::vec3(5, 5, 0), maths::vec2(4, 4), maths::vec4(1, 0, 1, 1), shader);
	Renderable2D sprite2(maths::vec3(7, 1, 0), maths::vec2(2, 3), maths::vec4(0, 0, 1, 1), shader);
	Simple2DRenderer renderer;
	
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePos(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));
		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.flush();

		window.update();
	}

	return 0;
}
