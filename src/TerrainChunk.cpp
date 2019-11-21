#include <TerrainChunk.h>

TerrainChunk::TerrainChunk()
	: position(), middlePoint(), size()
{
}

TerrainChunk::TerrainChunk(glm::ivec2 position, glm::ivec2 size, tools::Matrix<float> heightMap)
	: position(position), middlePoint({ position.x + (size.x / 2), position.y + (size.y / 2) }), size(size), heightMap(std::move(heightMap))
{
}

const tools::Matrix<float> &TerrainChunk::GetHeightMap() const
{
	return heightMap;
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
