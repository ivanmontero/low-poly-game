#include "main.h"
#include "renderer.h"
#include "window.h"
#include "mouse.h"
#include "keyboard.h"
#include "scene.h"
#include "world.h"

float Main::lastTime = 0;
float Main::delta = 0;
Scene* Main::currentScene = nullptr;

bool Main::Initialize() {
	int width = 1000, height = 800;
	if (!Window::Initialize(width, height)) {
		return false;
	}

	if (!Renderer::Initialize(width, height)) {
		return false;
	}

	Keyboard::Initialize();
	Mouse::Initialize();

	SetUpScenes();

	lastTime = glfwGetTime();
}

void Main::Run() {
	while (!Window::ShouldClose()) {
		UpdateDelta();
		Window::Poll();

		currentScene->Update(delta);
		currentScene->Render();

		Window::SwapBuffers();

		// Debug purposes
		if (Keyboard::IsKeyDown(GLFW_KEY_ESCAPE))
			Window::SetShouldClose(true);
	}
}

void Main::Exit() {
	Window::Dispose();
}

float Main::GetDelta() {
	return delta;
}

void Main::SetScene(Scene* scene) {
	currentScene = scene;
}

void Main::UpdateDelta() {
	float current = glfwGetTime();
	delta = current - lastTime;
	lastTime = current;
}

void Main::SetUpScenes() {
	World::GetInstance()->Initialize();

	currentScene = World::GetInstance();

}

int main() {
	if (!Main::Initialize()) {
		Main::Exit();
		return -1;
	}
	Main::Run();
	Main::Exit();
	return 0;
}
