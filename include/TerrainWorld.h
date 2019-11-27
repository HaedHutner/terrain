#ifndef _TERRAIN_WORLD_H
#define _TERRAIN_WORLD_H

#include <vector>
#include <optional>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <ChunkGrid.h>
#include <TerrainChunk.h>
#include <HeightMapGenerator.h>

const int CHUNK_WIDTH = 64;

const float HEIGHT_AMPLIFICATION = 100.0;

//constexpr std::vector<int> FetchChunkVertexIndices() {
//	std::vector<int> indices = std::vector<int>(CHUNK_WIDTH * CHUNK_WIDTH);
//
//	for (int i = 0; i < CHUNK_WIDTH * CHUNK_WIDTH; i += 6) {
//		indices[i    ] = i;
//		indices[i + 1] = i + 3;
//		indices[i + 2] = i + 4;
//		indices[i + 3] = i + 4;
//		indices[i + 4] = i;
//		indices[i + 5] = i + 1;
//	}
//
//	return indices;
//}
//
//constexpr std::vector<glm::vec2> FetchChunkVertices() {
//	std::array<glm::vec2, CHUNK_WIDTH * CHUNK_WIDTH> coordinates = std::array<glm::vec2, CHUNK_WIDTH * CHUNK_WIDTH>();
//
//	for (int i = 0; i < CHUNK_WIDTH * CHUNK_WIDTH; i++) {
//		coordinates[i] = { i % CHUNK_WIDTH, i / CHUNK_WIDTH };
//	}
//
//	return coordinates;
//}
//
//const std::vector<int> CHUNK_VERTEX_INDICES = FetchChunkVertexIndices();
//
//const std::vector<glm::vec2> CHUNK_VERTICES = FetchChunkVertices();

class TerrainWorld {
private:

	std::string name;

	HeightMapGenerator heightMapGenerator;

	ChunkGrid grid;

	TerrainChunk GenerateAndCacheSingleChunk(const glm::ivec2 &chunkCoordinates, const glm::ivec2 &size, const float &amplification);

public:

	TerrainWorld();

	TerrainWorld(std::string name, HeightMapGenerator heightMapGenerator);

	const TerrainChunk FetchChunkAt(glm::ivec2 absoluteCoordinates);

	const std::vector<TerrainChunk> FetchChunksAt(glm::ivec2 absoluteCoordinates, int radius = 1);

	const void GenerateChunkAt(glm::ivec2 absoluteCoordinates);

	const void GenerateChunksAt(glm::ivec2 absoluteCoordinates, int radius = 1);

	const std::optional<TerrainChunk> FetchCachedChunkAt(glm::ivec2 absoluteCoordiantes) const;

	const std::vector<TerrainChunk> FetchCachedChunksAt(glm::ivec2 absoluteCoordinates, int radius = 1) const;

};

#endif