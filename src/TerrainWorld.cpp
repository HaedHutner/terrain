#include <TerrainWorld.h>

TerrainChunk TerrainWorld::GenerateAndCacheSingleChunk(const glm::ivec2 &chunkCoordinates, const glm::ivec2 &size, const float &amplification)
{
	TerrainChunk newTerrainChunk = TerrainChunk(
		chunkCoordinates,
		heightMapGenerator.GenerateHeightMap(
			chunkCoordinates *( size.x - 1 ),
			{ size.x + 1, size.y + 1 }, // Increase size of heightmap by 1 in each direction to create skirt of extra vertices for later use ( like in normal calculations )
			128.0f,
			amplification
		)
	);

	grid.Insert(chunkCoordinates, newTerrainChunk);

	return newTerrainChunk;
}

TerrainWorld::TerrainWorld()
{
}

TerrainWorld::TerrainWorld(std::string name, HeightMapGenerator heightMapGenerator)
	: name(name), heightMapGenerator(heightMapGenerator)
{
}

const TerrainChunk TerrainWorld::FetchChunkAt(glm::ivec2 absoluteCoordinates)
{
	glm::ivec2 chunkCoordinates = { absoluteCoordinates.x / CHUNK_WIDTH, absoluteCoordinates.y / CHUNK_WIDTH };

	auto chunk = grid.FetchOne(chunkCoordinates);

	if (chunk.has_value()) {
		return chunk.value();
	}
	else {
		return GenerateAndCacheSingleChunk(chunkCoordinates, { CHUNK_WIDTH, CHUNK_WIDTH }, 255.0f);
	}
}

const std::vector<TerrainChunk> TerrainWorld::FetchChunksAt(glm::ivec2 absoluteCoordinates, int radius)
{
	if (radius == 0) {
		return std::vector<TerrainChunk>{ FetchChunkAt(absoluteCoordinates) };
	}
	else {
		std::vector<TerrainChunk> result = std::vector<TerrainChunk>();

		for (int i = -radius; i < radius; i++) {
			for (int j = -radius; j < radius; j++) {
				glm::ivec2 chunkCoordinates = { (absoluteCoordinates.x / CHUNK_WIDTH) + i, (absoluteCoordinates.y / CHUNK_WIDTH) + j };

				auto chunk = grid.FetchOne(chunkCoordinates);

				if (chunk.has_value()) {
					result.push_back(chunk.value());
				}
				else {
					TerrainChunk newTerrainChunk = GenerateAndCacheSingleChunk(chunkCoordinates, { CHUNK_WIDTH, CHUNK_WIDTH }, 100.0f);

					result.push_back(newTerrainChunk);
				}
			}
		}

		return result;
	}
}

const void TerrainWorld::GenerateChunkAt(glm::ivec2 absoluteCoordinates)
{
	glm::ivec2 chunkCoordinates = { absoluteCoordinates.x / CHUNK_WIDTH, absoluteCoordinates.y / CHUNK_WIDTH };

	auto chunk = grid.FetchOne(chunkCoordinates);

	if (chunk.has_value()) {
		return;
	}
	else {
		GenerateAndCacheSingleChunk(chunkCoordinates, { CHUNK_WIDTH, CHUNK_WIDTH }, 255.0f);
	}
}

const void TerrainWorld::GenerateChunksAt(glm::ivec2 absoluteCoordinates, int radius)
{
	if (radius == 0) {
		GenerateChunkAt(absoluteCoordinates);
	}
	else {
		for (int i = -radius; i < radius; i++) {
			for (int j = -radius; j < radius; j++) {
				glm::ivec2 chunkCoordinates = { (absoluteCoordinates.x / CHUNK_WIDTH) + i, (absoluteCoordinates.y / CHUNK_WIDTH) + j };

				auto chunk = grid.FetchOne(chunkCoordinates);

				if (chunk.has_value()) {
					continue;
				}
				else {
					GenerateAndCacheSingleChunk(chunkCoordinates, { CHUNK_WIDTH, CHUNK_WIDTH }, 255.0f);
				}
			}
		}
	}
}

const std::optional<TerrainChunk> TerrainWorld::FetchCachedChunkAt(glm::ivec2 absoluteCoordinates) const
{
	return grid.FetchOne({ absoluteCoordinates.x / CHUNK_WIDTH, absoluteCoordinates.y / CHUNK_WIDTH });
}

const std::vector<TerrainChunk> TerrainWorld::FetchCachedChunksAt(glm::ivec2 absoluteCoordinates, int radius) const
{
	return grid.Fetch({ absoluteCoordinates.x / CHUNK_WIDTH, absoluteCoordinates.y / CHUNK_WIDTH }, radius);
}
