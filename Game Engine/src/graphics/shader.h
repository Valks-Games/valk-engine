#pragma once

#include "renderer.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace valk {
	namespace graphics {
		struct ShaderProgramSource
		{
			std::string VertexSource;
			std::string FragmentSource;
		};

		ShaderProgramSource parseShader(const std::string& filepath);

		GLuint compileShader(GLuint type, const std::string& source);

		GLuint createShader(const std::string& vertexShader, const std::string& fragmentShader);
	}
}
