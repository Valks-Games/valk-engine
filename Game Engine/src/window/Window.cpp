#include "window.h"

void window_resize(GLFWwindow* window, int width, int height);

Window::Window(const char *title, int width, int height) 
{
	m_Title = title;
	m_Width = width;
	m_Height = height;
	if (!Init())
		glfwTerminate();

	for (int i = 0; i < MAX_KEYS; i++)
	{
		m_Keys[i] = false;
	}

	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		m_MouseButtons[i] = false;
	}
}

Window::~Window() 
{
	glfwTerminate();
}

bool Window::Init()
{
	if (glfwInit() == GLFW_PLATFORM_ERROR)
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	if (!m_Window)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowSizeCallback(m_Window, window_resize);
	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	glfwSetCursorPosCallback(m_Window, cursor_position_callback);
	glfwSwapInterval(1);

	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Failed to initialize GLEW!" << std::endl;
		return false;
	}
		
	return true;
}

bool Window::isKeyDown(unsigned int keycode) const
{
	//TODO: Log this!
	if (keycode >= MAX_KEYS)
		return false;
	return m_Keys[keycode];
}

bool Window::isMouseDown(unsigned int button) const
{
	//TODO: Log this!
	if (button >= MAX_BUTTONS)
		return false;
	return m_MouseButtons[button];
}

void Window::getMousePos(double& x, double& y) const
{
	x = mx;
	y = my;
}

void Window::Clear() const 
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

bool Window::Closed() const
{
	return glfwWindowShouldClose(m_Window);
}

void window_resize(GLFWwindow* window, int width, int height) 
{
	GLCall(glViewport(0, 0, width, height));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	Window* win = (Window*) glfwGetWindowUserPointer(window);
	win->m_Keys[key] = action != GLFW_RELEASE;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) 
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_MouseButtons[button] = action != GLFW_RELEASE;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) 
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->mx = xpos;
	win->my = ypos;
}