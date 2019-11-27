#include <TerrainChunk.h>

TerrainChunk::TerrainChunk()
	: position(), middlePoint(), size()
{
}

TerrainChunk::TerrainChunk(glm::ivec2 position, tools::Matrix<float> heightMap)
	: position(position), middlePoint({ position.x + (heightMap[0].size() / 2), position.y + (heightMap.size() / 2) }), size({heightMap[0].size(), heightMap.size()}), heights(heightMap[0].size() * heightMap.size())
{
	for (int i = 0; i < size.x * size.y; i++) {
		int x = i % size.x;
		int y = i / size.y;

		heights[i] = glm::vec4(heightMap[y][x], 0.0f, 0.0f, 0.0f);
	}
}

const float TerrainChunk::GetHeightAt(int x, int y) const
{
	int k = x + size.x * y;
	return heights[k].x;
}

const std::vector<glm::vec4>&TerrainChunk::GetHeights() const
{
	return heights;
}

const glm::vec2& TerrainChunk::GetMiddlePoint() const
{
	return middlePoint;
}

const glm::ivec2 &TerrainChunk::GetPosition() const
{
	return position;
}

const glm::ivec2 &TerrainChunk::GetSize() const
{
	return size;
}

const AABB& TerrainChunk::GetAABB() const
{
	return AABB(glm::vec3(), glm::vec3());
}
