#include "shader.h"

namespace valk {
	namespace graphics {

		Shader::Shader(const char* vertPath, const char* fragPath)
			: m_VertPath(vertPath), m_FragPath(fragPath)
		{
			m_ShaderID = load();
		}

		Shader::~Shader() 
		{
			GLCall(glDeleteProgram(m_ShaderID));
		}

		GLuint Shader::load() 
		{
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSourceString = FileUtils::read_file(m_VertPath);
			std::string fragSourceString = FileUtils::read_file(m_FragPath);

			const char* vertSource = vertSourceString.c_str();
			const char* fragSource = fragSourceString.c_str();

			GLCall(glShaderSource(vertex, 1, &vertSource, NULL));
			GLCall(glCompileShader(vertex));

			GLint result;
			GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &result));
			if (result == GL_FALSE) 
			{
				GLint length;
				GLCall(glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length));
				std::vector<char> error(length);
				GLCall(glGetShaderInfoLog(vertex, length, &length, &error[0]));
				std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
				GLCall(glDeleteShader(vertex));
				return 0;
			}

			GLCall(glShaderSource(fragment, 1, &fragSource, NULL));
			GLCall(glCompileShader(fragment));

			GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &result));
			if (result == GL_FALSE)
			{
				GLint length;
				GLCall(glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length));
				std::vector<char> error(length);
				GLCall(glGetShaderInfoLog(fragment, length, &length, &error[0]));
				std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
				GLCall(glDeleteShader(fragment));
				return 0;
			}

			GLCall(glAttachShader(program, vertex));
			GLCall(glAttachShader(program, fragment));

			GLCall(glLinkProgram(program));
			GLCall(glValidateProgram(program));

			GLCall(glDeleteShader(vertex));
			GLCall(glDeleteShader(fragment));

			return program;
		}

		GLint Shader::getUniformLocation(const GLchar* name) 
		{
			return glGetUniformLocation(m_ShaderID, name);
		}

		void Shader::setUniform1f(const GLchar* name, float value) 
		{
			GLCall(glUniform1f(getUniformLocation(name), value));
		}

		void Shader::setUniform1i(const GLchar* name, int value) 
		{
			GLCall(glUniform1i(getUniformLocation(name), value));
		}

		void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector) 
		{
			GLCall(glUniform2f(getUniformLocation(name), vector.x, vector.y));
		}

		void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector)
		{
			GLCall(glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z));
		}

		void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector)
		{
			GLCall(glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w));
		}

		void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix) 
		{
			GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements));
		}

		void Shader::enable() const
		{
			GLCall(glUseProgram(m_ShaderID));
		}

		void Shader::disable() const
		{
			GLCall(glUseProgram(0));
		}
	}
}
