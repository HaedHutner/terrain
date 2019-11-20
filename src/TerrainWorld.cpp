#include <TerrainWorld.h>

TerrainWorld::TerrainWorld(HeightMapGenerator heightMapGenerator)
	: heightMapGenerator(heightMapGenerator)
{
}

std::vector<TerrainChunk> TerrainWorld::FetchChunksAt(glm::vec2 absoluteCoordinates, int radius)
{
	glm::ivec2 chunkCoordinates = { absoluteCoordinates.x / CHUNK_WIDTH, absoluteCoordinates.y / CHUNK_WIDTH };
	


	return std::vector<TerrainChunk>();
}
