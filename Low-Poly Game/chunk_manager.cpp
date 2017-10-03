#include <iostream>
#include "chunk_manager.h"
#include "fast_noise.h"
#include "renderer.h"
#include "timer.h"

std::unordered_map<P, Chunk*, pair_hash>	ChunkManager::chunks;
std::set<Chunk*, load_comp>							ChunkManager::loadedChunks;
FastNoise									ChunkManager::noise;
P											ChunkManager::currentChunk;
float										ChunkManager::maxRenderTime = 0.01f;
int											ChunkManager::renderDistance = 10;

void ChunkManager::Initialize(float x, float z, int seed) {
	noise.SetSeed(seed);
	int cx = floor(x / CHUNK_WIDTH);
	int cz = floor(z / CHUNK_WIDTH);
	Update(cx, cz);
	//for (int i = cx - renderDistance; i <= cx + renderDistance; i++) {
	//	for (int k = cz - renderDistance; k <= cz + renderDistance; k++) {
	//		Load(i, k);
	//	}
	//}
	//currentChunk = P(cx, cz);
}

// MOST COSTLY
void ChunkManager::Update(float x, float z) {
	int cx = floor(x / CHUNK_WIDTH);
	int cz = floor(z / CHUNK_WIDTH);
	// PUT ALL IN TIMER
	// Check if any currently loaded ones are out of bounds
	std::set<Chunk*, load_comp>::iterator it;
	for (it = loadedChunks.begin(); it != loadedChunks.end();) {
		if ((*it)->GetRadius(cx, cz) > renderDistance) {
			loadedChunks.erase(it++);
		} else {
			it++;
		}
	}

	// Load chunks that are in range
	// Load from inside out
	// X = starting point
	//	X - > - +
	//	|		|
	//	^		v
	//	|		|
	//	+ - < -	X
	// Edit: Timer to make sure that the game doesn't hang. 
	// TODO: Replace with new thread
	Timer timer;
	bool stop = false;
	timer.Start();
	for (int r = 0; r <= renderDistance; r++) {
		// on the X
		for (int i = -r; i <= r; i++) {
			if (r % 2 == 0) {		// If loop unnecessary; just for fancies
				Load(cx + i, cz + r);
				Load(cx - i, cz - r);
			} else {
				Load(cx - i, cz + r);
				Load(cx + i, cz - r);
			}
			if (timer.GetDelta() > maxRenderTime) {
				stop = true;
				break;
			}
		}
		if (stop) break;
		// on the Z
		if (!stop) {
			for (int i = -r; i <= r; i++) {
				if (r % 2 == 0) {
					Load(cx + r, cz + i);
					Load(cx - r, cz - i);
				} else {
					Load(cx - r, cz + i);
					Load(cx + r, cz - i);
				}
				if (timer.GetDelta() > maxRenderTime) {
					stop = true;
					break;
				}
			}
		}
		if (stop) break;
	}
	timer.Stop();
	if(timer.GetDelta() > .005f)
		std::cout << timer.GetDelta() << std::endl;

}

void ChunkManager::SetRenderDistance(int dist) {
	renderDistance = dist;
}

void ChunkManager::Render() {
	//for (int i = 0; i < loadedChunks.size(); i++)		// Vector
	//	Renderer::Render(loadedChunks.at(i)->mesh);

	for (auto c : loadedChunks)
		Renderer::Render(c->mesh);

	//for (auto const& x : chunks) {
	//	Renderer::Render(x.second->mesh);
	//}

}

void ChunkManager::SetMaxRenderTime(float time) {
	maxRenderTime = time;
}

void ChunkManager::Release() {
	for (std::unordered_map<P, Chunk*, pair_hash>::iterator it = chunks.begin(); it != chunks.end(); it++) {
		it->second->Delete();
		delete it->second;
	}
}

void ChunkManager::Load(int cx, int cz) {
	std::unordered_map<P, Chunk*, pair_hash>::iterator it = chunks.find(P(cx, cz));
	// check that the chunk exists
	if (it != chunks.end()) {
		// check that chunk isn't already loaded
		if (loadedChunks.find(it->second) == loadedChunks.end()) {
			loadedChunks.insert(it->second);
		}
	} else {
		Generate(cx, cz);
		loadedChunks.insert(chunks.at(P(cx, cz)));
	}
}

void ChunkManager::Generate(int cx, int cz) {
	// Noise at (x,y) located at vals[y * (CHUNK_TILES + 1) + x]	<-	Located at the edges
	// Noise for midpoints at tile (x, y) is at 
	// vals[(CHUNK_TILES + 1) * (CHUNK_TILES + 1) + y * CHUNK_TILES + x
	std::vector<float> vals;

	float wcx = (float)cx * CHUNK_WIDTH; // FLOAT
	float wcz = (float)cz * CHUNK_WIDTH;
	// Creates the edges of the tile values
	for (int i = 0; i <= CHUNK_TILES; i++) {
		for (int k = 0; k <= CHUNK_TILES; k++) {
			vals.push_back(GetNoiseValue(
				wcx + TILE_WIDTH * i, 
				wcz + TILE_WIDTH * k
			));
		}
	}
	// Creates values for midpoints
	for (int i = 0; i < CHUNK_TILES; i++) {
		for (int k = 0; k < CHUNK_TILES; k++) {
			vals.push_back(GetNoiseValue(
				wcx + TILE_WIDTH / 2.0f + TILE_WIDTH * i,
				wcz + TILE_WIDTH / 2.0f + TILE_WIDTH * k
			));
		}
	}

	chunks.insert(chunk_pair(P(cx, cz), new Chunk(cx, cz, CHUNK_WIDTH, vals)));
}

// Where all the terrain magic happens
float ChunkManager::GetNoiseValue(float x, float z) {
	float value = 0;
	/*****************TRY 1 *****************/
	float lacunarity = 2.0f;
	float persistance = 0.5f;

	// Roughness of terrain		// Experimental
	float rough = .5f + Clamp(noise.GetPerlinFractal(x / 30.0f, z / 30.0f));

	float vmult= 12.0f * rough;
	float hmult = 1.0f * rough;		// Smaller = wider

	// General terrain
	float octaves = 10;
	for (int i = 0; i < octaves; i++) {
		float frequency = pow(lacunarity, i) * hmult;
		float amplitude = pow(persistance, i) * vmult;
		value += amplitude * noise.GetPerlin(x * frequency, z * frequency);
	}
	// Mountains
	value += 100.0f * pow(Clamp(noise.GetPerlin(x, z)), 5);	
	value += (500.0f * (pow(Clamp(noise.GetPerlin(x / 5.0f, z / 5.0f)), 5) - 0.03125)); 	// 0.03125 is when noise returns .5

	//value += -25.0f * pow(Clamp(noise.GetPerlin(x * 2.0f, z * 2.0f)), 5);	// Depressions

	// Giant mountains?
	// Experimental
	value += (3000.0f * (pow(Clamp(noise.GetPerlin(x / 20.0f, z / 20.0f)), 5) - 0.03125)); 	// 0.03125 is when noise returns .5
	/*****************TRY 1 *****************/




	return value;

	//return 1.0f * noise.GetPerlin(x * 50.0f, z * 50.0f)
	//	+ 2.5f * noise.GetPerlin(x * 25.0f, z * 25.0f)
	//	+ 10.0f * noise.GetPerlinFractal(x * 12.5f, z * 12.5f);
	//return 10.0f * noise.GetValue(x * 4.0f, z * 4.0f);
		//+ 5.0f * noise.GetPerlin(x * 6.5f, z * 6.5f);
}

float ChunkManager::Clamp(float n) { return 0.5f * n + 0.5f; }
