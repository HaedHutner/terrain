#ifndef _TERRAIN_WORLD_H
#define _TERRAIN_WORLD_H

#include <array>
#include <vector>

#include <glm/glm.hpp>

#include <TerrainChunk.h>
#include <HeightMapGenerator.h>

const int CHUNK_WIDTH = 64;

constexpr std::vector<int> FetchChunkVertexIndices() {
	std::vector<int> indices = std::vector<int>(CHUNK_WIDTH * CHUNK_WIDTH);

	for (int i = 0; i < CHUNK_WIDTH * CHUNK_WIDTH; i += 6) {
		indices[i    ] = i;
		indices[i + 1] = i + 3;
		indices[i + 2] = i + 4;
		indices[i + 3] = i + 4;
		indices[i + 4] = i;
		indices[i + 5] = i + 1;
	}

	return indices;
}

constexpr std::vector<glm::vec2> FetchChunkVertices() {
	std::array<glm::vec2, CHUNK_WIDTH * CHUNK_WIDTH> coordinates = std::array<glm::vec2, CHUNK_WIDTH * CHUNK_WIDTH>();

	for (int i = 0; i < CHUNK_WIDTH * CHUNK_WIDTH; i++) {
		coordinates[i] = { i % CHUNK_WIDTH, i / CHUNK_WIDTH };
	}

	return coordinates;
}

const std::vector<int> CHUNK_VERTEX_INDICES = FetchChunkVertexIndices();

const std::vector<glm::vec2> CHUNK_VERTICES = FetchChunkVertices();

class TerrainWorld {
private:

	HeightMapGenerator heightMapGenerator;

	std::vector<TerrainChunk> chunks;

public:

	TerrainWorld(HeightMapGenerator heightMapGenerator);

	std::vector<TerrainChunk> FetchChunksAt(glm::vec2 absoluteCoordinates, int radius = 1);

};

#endif