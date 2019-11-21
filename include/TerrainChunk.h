#ifndef _TERRAIN_CHUNK_H
#define _TERRAIN_CHUNK_H

#include <memory>

#include <glm/glm.hpp>

#include <Matrix.h>

class TerrainChunk {

private:

    tools::Matrix<float> heightMap;

	glm::ivec2 position;

	glm::vec2 middlePoint;

	glm::ivec2 size;

public:

	TerrainChunk();

	TerrainChunk(glm::ivec2 position, glm::ivec2 size, tools::Matrix<float> heightMap);

	const tools::Matrix<float> &GetHeightMap() const;

	const glm::vec2 &GetMiddlePoint() const;

	const glm::ivec2 &GetPosition() const;

	const glm::ivec2 &GetSize() const;

};

#endif