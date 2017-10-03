#pragma once
#include <GLFW/glfw3.h>

typedef struct SIZE {
	int width;
	int height;
};

class Window {
private:
	static GLFWwindow* window;
public:
	static bool Initialize(int width, int height);
	static void Resize(int width, int height);
	static void Show();
	static void Hide();
	static void Dispose();
	static void Poll();
	static void SwapBuffers();

	static void GrabCursor(bool grab);

	static void SetVSync(bool vsync);
	static void SetFullscreen(bool fullscreen);		// TODO

	static void SetShouldClose(bool close);
	static bool ShouldClose();

	static SIZE GetSize();

};

void ResizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void CursorCallback(GLFWwindow* window, double xpos, double ypos);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
