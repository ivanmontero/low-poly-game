#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "scene.h"
#include "fast_noise.h"

class Mesh;

class World : public Scene {
private:
	//float r = 0, g = 1.0f/3.0f, b = 2.0f/3.0f;
	Mesh* cube;
	GLuint shader;
	glm::mat4 model;
	FastNoise noise;
	bool wireframe = true, chunkLoading = true;
	float time, speed, maxRenderTime;
	int renderDistance = 10;
public:
	void Initialize();  
	void Update(float delta);
	void Render();
	void Release();

	static World* GetInstance();
private:
	static World instance;
	World();
};