#pragma once

class Scene;

class Main {
private:
	static float lastTime;
	static float delta;
	static Scene* currentScene;
public:
	static bool Initialize();
	static void Run();
	static void Exit();
	static float GetDelta();
	static void SetScene(Scene* scene);
private:
	static void UpdateDelta();
	// FILL WITH SCENES and set curentScene.
	static void SetUpScenes();
};