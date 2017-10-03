#pragma once
#include <GLFW/glfw3.h>
#include <queue>

class Scene;

struct KeyEvent {
	int key;
	int scancode;
	int action;
	int mode;
	KeyEvent(int key, int scancode, int action, int mode) 
		: key(key), scancode(scancode), action(action), mode(mode) {}
	KeyEvent() {};
};

class Keyboard {
private:
	static bool keys[1024];
	static std::queue<KeyEvent> keyEvents;
public:
	static void Initialize();
	static void KeyCallback(int key, int scancode, int action, int mode);

	// Methods for non-event-based

	static bool IsKeyDown(int key);

	// Methods for event-based
	
	static bool NextEvent();
	static int GetEventKey();
	static bool GetEventKeyState();

public:
	static KeyEvent Event;	// current event
};
