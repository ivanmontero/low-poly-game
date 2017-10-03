#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>

#include "window.h"
#include "renderer.h"
#include "keyboard.h"
#include "mouse.h"

GLFWwindow* Window::window = nullptr;

bool Window::Initialize(int width, int height) {
	if (!window) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	} else {
		Dispose();
	}

	window = glfwCreateWindow(width, height, "Window", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, ResizeCallback);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetCursorPosCallback(window, CursorCallback);

	return true;
}

void Window::Resize(int width, int height) {
	glfwSetWindowSize(window, width, height);
	Renderer::Resize(width, height);
}

void Window::Show() {
	glfwShowWindow(window);
}

void Window::Hide() {
	glfwHideWindow(window);
}

void Window::Dispose() {
	glfwDestroyWindow(window);
}

void Window::Poll() {
	glfwPollEvents();
}

void Window::SwapBuffers() {
	glfwSwapBuffers(window);
}

void Window::GrabCursor(bool grab) {
	glfwSetInputMode(window, GLFW_CURSOR, grab ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Window::SetVSync(bool vsync) {
	glfwSwapInterval(vsync);
}

void Window::SetShouldClose(bool close) {
	glfwSetWindowShouldClose(window, close);
}

bool Window::ShouldClose() {
	return glfwWindowShouldClose(window);
}

SIZE Window::GetSize() {
	SIZE s;
	glfwGetFramebufferSize(window, &s.width, &s.height);
	return s;
}

void ResizeCallback(GLFWwindow* window, int width, int height) {
	Renderer::Resize(width, height);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	Keyboard::KeyCallback(key, scancode, action, mode);
}

void CursorCallback(GLFWwindow* window, double xpos, double ypos) {
	Mouse::CursorCallback((float)xpos, (float)ypos);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	Mouse::ButtonCallback(button, action, mods);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	Mouse::ScrollCallback((float)xoffset, (float)yoffset);
}
