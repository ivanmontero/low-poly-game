#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "world.h"
#include "renderer.h"
#include "window.h"
#include "camera.h"
#include "keyboard.h"
#include "mouse.h"
#include "mesh.h"
#include "player.h"
#include "chunk_manager.h"

void World::Initialize() {
	cube = Renderer::CreateCube();
	model = glm::mat4();
	shader = Renderer::CreateShader("test.vert", "test.frag");
	noise = FastNoise();
	time = 0;
	speed = 10.0f;
	maxRenderTime = 0.01f;
	Window::GrabCursor(true);
	Window::SetVSync(true);
	//Player::z = 4.0f;
	Camera::SetPosition(0.0f, 10.0f, 0.0f);
	ChunkManager::Initialize(0.0f, 0.0f, 1337);
	Renderer::SetWireframe(true);
	Renderer::SetRenderDistance(10000.0f);
	//Renderer::SetCulling(true);
}

void World::Update(float delta) {
	// Input resolving - Event
	while (Keyboard::NextEvent()) {
		KeyEvent e = Keyboard::Event;
		if (e.action == PRESS) {
			//std::cout << "key pressed: " << e.key << std::endl;
			switch (e.key) {
			case KEY_TAB:
				wireframe = !wireframe;
				Renderer::SetWireframe(wireframe);
				break;
			case KEY_F1:
				chunkLoading = !chunkLoading;
				break;
			case KEY_RIGHT_BRACKET:
				ChunkManager::SetRenderDistance(++renderDistance);
				break;
			case KEY_LEFT_BRACKET:
				ChunkManager::SetRenderDistance(--renderDistance);
				break;
			}
		}
	}

	while (Mouse::NextEvent()) {
		MouseEvent e = Mouse::Event;
		switch (e.type) {
		case BUTTON:
			//if (e.action == PRESS) {
			//	std::cout << "mouse pressed: " << e.button << " (" << Mouse::GetX() << ", " << Mouse::GetY() << ")" << std::endl;
			//}
			break;
		case CURSOR:
			Player::RotateCamera(e.dx, e.dy);
			break;
		case SCROLL:
			speed += e.dy < 0 ? -2.0f : 2.0f;
			//Renderer::SetFOV(PI / 20.0f);
			break;
		}
	}

	// Input resolving - Pressed
	float cameraSpeed = speed * delta;

	if (Keyboard::IsKeyDown(KEY_W)) Camera::Move(Camera::GetFront() * cameraSpeed);
	if (Keyboard::IsKeyDown(KEY_S)) Camera::Move(-Camera::GetFront() * cameraSpeed);
	if (Keyboard::IsKeyDown(KEY_A)) Camera::Move(-Camera::GetRight() * cameraSpeed);
	if (Keyboard::IsKeyDown(KEY_D)) Camera::Move(Camera::GetRight() * cameraSpeed);
	if (Keyboard::IsKeyDown(KEY_SPACE)) Camera::Move(glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed);
	if (Keyboard::IsKeyDown(KEY_LEFT_SHIFT)) Camera::Move(glm::vec3(0.0f, -1.0f, 0.0f) * cameraSpeed);
	if (Keyboard::IsKeyDown(KEY_EQUAL)) {
		maxRenderTime += .001f;
		ChunkManager::SetMaxRenderTime(maxRenderTime);
	}
	if (Keyboard::IsKeyDown(KEY_MINUS)) {
		maxRenderTime -= .001f;
		ChunkManager::SetMaxRenderTime(maxRenderTime);
	}
	//if (Keyboard::IsKeyDown(KEY_RIGHT_BRACKET)) ChunkManager::SetRenderDistance(++renderDistance);
	//if (Keyboard::IsKeyDown(KEY_LEFT_BRACKET)) ChunkManager::SetRenderDistance(--renderDistance);

	//if (Keyboard::IsKeyDown(KEY_EQUAL))
	//	speed += .0005;
	//if (Keyboard::IsKeyDown(KEY_MINUS))
	//	speed -= .0005;

	//r += delta;
	//g += delta;
	//b += delta;
	//if (r > 1.0f) r -= 1.0f;
	//if (g > 1.0f) g -= 1.0f;
	//if (b > 1.0f) b -= 1.0f;
	//Camera::SetPosition(Player::x, 0, Player::z);
	time += delta; //* speed;

	//std::cout << "current chunk: X:" << floor(Camera::GetX() / CHUNK_WIDTH) 
	//	<< " Z:" << floor(Camera::GetZ() / CHUNK_WIDTH) << std::endl;

	//Camera::SetY(ChunkManager::GetNoiseValue(Camera::GetX(), Camera::GetZ()) + 3.0f);

	if(chunkLoading)
		ChunkManager::Update(Camera::GetX(), Camera::GetZ());

	// To follow the terrain
	//Camera::SetY(10 + ChunkManager::GetNoiseValue(Camera::GetX(), Camera::GetZ()));

}

void World::Render() {
	//Renderer::Clear(r, g, b, 1.0f);
	//Renderer::Clear(.2f, .3f, 1.0f, 1.0f);
	Renderer::Clear();
	Renderer::SetShader(shader);
	Renderer::SetLogarithicDepth();
	//Renderer::SetVAO(cube);

	model = glm::mat4();
	//model = glm::rotate(model, time, glm::vec3(1.0f));
	float n = noise.GetPerlin(time * 100, 0.0);
	//std::cout << n << " " << time <<std::endl;
	model = glm::translate(model, glm::vec3(0, n + 5.0f , 0));

	Renderer::SetUniform("model", model);
	Renderer::SetUniform("Color", 1.0f, 0.0f, 0.0f);
	//Renderer::Render(CUBE_INDICES);
	//Renderer::SetVAO(0);
	Renderer::Render(cube);

	//Renderer::SetUniform("Color", 0.0f, 1.0f, 0.0f);
	Renderer::SetUniform("model", glm::mat4());
	ChunkManager::Render();
	Renderer::SetShader(0);
}

void World::Release() {
	delete cube;
	ChunkManager::Release();
}

World World::instance = World();

World* World::GetInstance() {	return &instance;	}

World::World() {}
