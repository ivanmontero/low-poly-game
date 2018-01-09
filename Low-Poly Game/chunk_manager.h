#pragma once
#include <unordered_map>
#include <vector>
#include <set>
#include "chunk.h"

// TODO: Send all chunks at once

// Convention:
//	-	c -> chunk coordinates
//	-	w -> world coordinates
#define CHUNK_WIDTH 128.0f
#define TILE_WIDTH (CHUNK_WIDTH / CHUNK_TILES)
#define P std::pair<int, int>
#define chunk_pair std::pair<P, Chunk*>

class FastNoise;
struct pair_hash;
struct load_comp;

class ChunkManager {
private:
	static std::unordered_map<P, Chunk*, pair_hash> chunks;
	static std::set<Chunk*, load_comp> loadedChunks;

	static FastNoise noise;
	
	static float maxRenderTime;
	static int renderDistance;
	static P currentChunk;
public:
	static void Initialize(float x, float z, int seed);

	// Algorithm:
	//  - Search loaded chunks to see if any should be unloaded
	//  - Look in circles around current position to find chunks to load
	//	- TODO: Add writing to files and remove chunks that are extremely far
	static void Update(float x, float z);		//TODO: Do in a new thread
	static void SetRenderDistance(int dist);
	static void Render();

	static void SetMaxRenderTime(float time);	// EXPERMENTAL; for debugging purposes. Extreme lag

	static void Release();

	static float GetNoiseValue(float x, float z);

private:
	static void Load(int cx, int cz);
	static void Unload(int cx, int cz);
	static void Generate(int cx, int cz);

	static float Clamp(float n);
};

// Only for pairs of std::hash-able types for simplicity.
// You can of course template this struct to allow other hash functions
struct pair_hash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2> &p) const {
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);

		// Mainly for demonstration purposes, i.e. works but is overly simple
		// In the real world, use sth. like boost.hash_combine
		return h1 ^ h2;
	}
};


struct load_comp {
	// True if goes before
	bool operator() (const Chunk* c1, const Chunk* c2) const {
		if (c1->cx != c2->cx)
			return c1->cx < c2->cx;
		return c1->cz < c2->cz;
	}
};