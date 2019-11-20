#include <TerrainChunk.h>

TerrainChunk::TerrainChunk(glm::ivec2 position, glm::ivec2 size, tools::Matrix<float> heightMap)
	: position(position), size(size), heightMap(std::move(heightMap))
{
}

const tools::Matrix<float> &TerrainChunk::GetHeightMap() const
{
	return heightMap;
}

const glm::ivec2 &TerrainChunk::GetPosition() const
{
	return position;
}

const glm::ivec2 &TerrainChunk::GetSize() const
{
	return size;
}
