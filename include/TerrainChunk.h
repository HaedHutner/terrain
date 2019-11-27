#ifndef _TERRAIN_CHUNK_H
#define _TERRAIN_CHUNK_H

#include <memory>

#include <glm/glm.hpp>

#include <Matrix.h>
#include <renderer/AABB.h>

class TerrainChunk {

private:

    std::vector<glm::vec4> heights;

	glm::ivec2 position;

	glm::vec2 middlePoint;

	glm::ivec2 size;

	// AABB aabb;

public:

	TerrainChunk();

	TerrainChunk(glm::ivec2 position, tools::Matrix<float> heightMap);

	const float GetHeightAt(int x, int y) const;

	const std::vector<glm::vec4> &GetHeights() const;

	const glm::vec2 &GetMiddlePoint() const;

	const glm::ivec2 &GetPosition() const;

	const glm::ivec2 &GetSize() const;

	const AABB &GetAABB() const;
};

#endif