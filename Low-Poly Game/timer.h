#pragma once
#include <GLFW\glfw3.h>

class Timer {
private:
	static float startTime;
	static float endTime;
public:
	static void Start() {
		startTime = glfwGetTime();
		endTime = -1.0f;
	}
	static void Stop() {
		endTime = glfwGetTime();
	}

	static float GetDelta() {
		return (endTime == -1.0f ? glfwGetTime() : endTime) - startTime;
	}

	static void Reset() {
		startTime = -1;
		endTime = -1;
	}
};

float Timer::startTime = -1;
float Timer::endTime = -1;