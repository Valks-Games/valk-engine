#pragma once

#include "../graphics/Renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>

constexpr int MAX_KEYS = 1024;
constexpr int MAX_BUTTONS = 32;

class Window
{
private:
	const char* m_Title;
	int m_Width, m_Height;
	GLFWwindow *m_Window;
	bool m_Closed;

	bool m_Keys[MAX_KEYS];
	bool m_MouseButtons[MAX_BUTTONS];
	double mx, my;
public:
	Window(const char *title, int width, int height);
	~Window();
	void Clear() const;
	void Update();
	bool Closed() const;

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }

	bool isKeyDown(unsigned int keycode) const;
	bool isMouseDown(unsigned int button) const;
	void getMousePos(double& x, double& y) const;
private:
	bool Init();
	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
};