#ifndef _CHUNK_GRID_H
#define _CHUNK_GRID_H

#include <iostream>
#include <unordered_map>
#include <optional>

#include <glm/glm.hpp>

#include <Matrix.h>
#include <TerrainChunk.h>

struct ChunkGridKeyFuncs
{
	size_t operator()(const glm::ivec2& k)const
	{
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}

	bool operator()(const glm::ivec2& a, const glm::ivec2& b)const
	{
		return a.x == b.x && a.y == b.y;
	}
};

class ChunkGrid {

private:

	std::unordered_map<glm::ivec2, TerrainChunk, ChunkGridKeyFuncs, ChunkGridKeyFuncs> grid;

public:

	ChunkGrid();

	void Insert(glm::ivec2 chunkCoordinates, TerrainChunk chunk);

	const std::optional<TerrainChunk> FetchOne(glm::ivec2 chunkCoordinates) const;

	const std::vector<TerrainChunk> Fetch(glm::ivec2 chunkCoordinates, int radius = 0) const;
};

#endif