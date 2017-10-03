#pragma once
#include <glm\glm.hpp>
#include "mesh.h"

//For one side
#define CHUNK_TILES 16	

#define TILE_LT 0
#define TILE_LB 1
#define TILE_RB 2
#define TILE_RT 3
#define TILE_M  4
#define TILE_TOP	0
#define TILE_LEFT   1
#define TILE_BOTTOM 2
#define TILE_RIGHT  3
struct Tile {
	glm::vec3 v[5];
	glm::vec3 n[4];
};

class Chunk {
public:
	// Range [0, CHUNK_SIZE]
	Tile* tiles[CHUNK_TILES][CHUNK_TILES];
	Mesh* mesh;
	int cx;
	int cz;
	float tileWidth;
public:
	// Pass in width
	Chunk(int cx, int cz, float width, std::vector<float> vals);
	
	// Find the square that it is in,
	// determine what triangle it is in,
	// then determine it's point
	float GetY(float x, float z);
	// Parameters are in CHUNK coordinates
	int GetRadius(int cx, int cz);

	void Delete();
};