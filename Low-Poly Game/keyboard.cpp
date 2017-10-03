#include "keyboard.h"
#include "constants.h"

bool Keyboard::keys[1024] = {};
std::queue<KeyEvent> Keyboard::keyEvents;
KeyEvent Keyboard::Event;

void Keyboard::Initialize() {}

void Keyboard::KeyCallback(int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;

	keyEvents.push(KeyEvent(key, scancode, action, mode));
}

bool Keyboard::IsKeyDown(int key) {
	return keys[key];
}

bool Keyboard::NextEvent() {
	if (keyEvents.empty())
		return false;
	Event = keyEvents.front();
	keyEvents.pop();
	return true;
}

int Keyboard::GetEventKey() {
	return Event.key;
}

bool Keyboard::GetEventKeyState() {
	return Event.action == GLFW_PRESS;
}


