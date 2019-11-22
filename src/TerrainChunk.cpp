#include <TerrainChunk.h>

TerrainChunk::TerrainChunk()
	: position(), middlePoint(), size()
{
}

TerrainChunk::TerrainChunk(glm::ivec2 position, glm::ivec2 size, tools::Matrix<float> heightMap)
	: position(position), middlePoint({ position.x + (size.x / 2), position.y + (size.y / 2) }), size(size), heights(size.x * size.y)
{
	for (int i = 0; i < size.x * size.y; i++) {
		int x = i % size.x;
		int y = i / size.y;

		heights[i] = heightMap[y][x];
	}
}

const float TerrainChunk::GetHeightAt(int x, int y) const
{
	int k = x + size.x * y;
	return heights[k];
}

const std::vector<float> &TerrainChunk::GetHeights() const
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
