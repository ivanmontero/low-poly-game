#include "chunk.h"
#include <iostream>

// * - . - *
// | \ 0 / |
// . 1 * 3 .
// | / 2 \ |
// * - . - *

// Construct the mesh
Chunk::Chunk(int cx, int cz, float width, std::vector<float> vals) : cx(cx), cz(cz) {
	//	+ - - - > +X
	//	|
	//	|
	//	v
	//	+Z
	// With values
	std::vector<Vertex> v;
	tileWidth = width / CHUNK_TILES; // total width will be passed in. Find by dividing CHUNK_TILES
	for (int x = 0; x < CHUNK_TILES; x++) {
		for (int z = 0; z < CHUNK_TILES; z++) {
			Tile* t = new Tile();
			float wcx = (float)cx * width; // FLOAT
			float wcz = (float)cz * width;
			// Optimization: use vertices from neighboring tiles ~4x less space
			// Vertices
			t->v[TILE_LT] = glm::vec3(wcx + tileWidth * x, vals.at(x * (CHUNK_TILES + 1) + z), wcz + tileWidth * z);
			t->v[TILE_LB] = glm::vec3(wcx + tileWidth * x, vals.at(x * (CHUNK_TILES + 1) + (z + 1)), wcz + tileWidth * (z + 1));
			t->v[TILE_RB] = glm::vec3(wcx + tileWidth * (x + 1), vals.at((x + 1) * (CHUNK_TILES + 1) + (z + 1)), wcz + tileWidth * (z + 1));
			t->v[TILE_RT] = glm::vec3(wcx + tileWidth * (x + 1), vals.at((x + 1) * (CHUNK_TILES + 1) + z), wcz + tileWidth * z);
			t->v[TILE_M]  = glm::vec3(wcx + tileWidth * x + tileWidth / 2, vals.at((CHUNK_TILES + 1) * (CHUNK_TILES + 1) + x * CHUNK_TILES + z),
						wcz + tileWidth * z + tileWidth / 2);

			// Normals
			t->n[TILE_TOP]    = glm::normalize(glm::cross(t->v[TILE_RT] - t->v[TILE_M], t->v[TILE_LT] - t->v[TILE_M]));
			t->n[TILE_LEFT]   = glm::normalize(glm::cross(t->v[TILE_LT] - t->v[TILE_M], t->v[TILE_LB] - t->v[TILE_M]));
			t->n[TILE_BOTTOM] = glm::normalize(glm::cross(t->v[TILE_LB] - t->v[TILE_M], t->v[TILE_RB] - t->v[TILE_M]));
			t->n[TILE_RIGHT]  = glm::normalize(glm::cross(t->v[TILE_RB] - t->v[TILE_M], t->v[TILE_RT] - t->v[TILE_M]));

			// Add vertices
			// TOP
			v.push_back(Vertex(t->v[TILE_M], t->n[TILE_TOP]));
			v.push_back(Vertex(t->v[TILE_RT], t->n[TILE_TOP]));
			v.push_back(Vertex(t->v[TILE_LT], t->n[TILE_TOP]));

			// LEFT
			v.push_back(Vertex(t->v[TILE_M], t->n[TILE_LEFT]));
			v.push_back(Vertex(t->v[TILE_LT], t->n[TILE_LEFT]));
			v.push_back(Vertex(t->v[TILE_LB], t->n[TILE_LEFT]));

			// BOTTOM
			v.push_back(Vertex(t->v[TILE_M], t->n[TILE_BOTTOM]));
			v.push_back(Vertex(t->v[TILE_LB], t->n[TILE_BOTTOM]));
			v.push_back(Vertex(t->v[TILE_RB], t->n[TILE_BOTTOM]));

			// RIGHT
			v.push_back(Vertex(t->v[TILE_M], t->n[TILE_RIGHT]));
			v.push_back(Vertex(t->v[TILE_RB], t->n[TILE_RIGHT]));
			v.push_back(Vertex(t->v[TILE_RT], t->n[TILE_RIGHT]));

			tiles[z][x] = t;
		}
	}
	// FINISH
	std::vector<GLuint> i;
	for (int j = 0; j < v.size(); j++)
		i.push_back(j);

	// TODO: Indices
	mesh = new Mesh(v, i);
}

int Chunk::GetRadius(int cx, int cz) {
	int dx = abs(this->cx - cx);
	int dy = abs(this->cz - cz);
	return dx > dy ? dx : dy;
}

void Chunk::Delete() {
	for (int i = 0; i < CHUNK_TILES; ++i) {
		delete[] tiles[i];
	}
	delete[] tiles;
}
