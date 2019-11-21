#include <TerrainWorld.h>

TerrainWorld::TerrainWorld()
{
}

TerrainWorld::TerrainWorld(std::string name, HeightMapGenerator heightMapGenerator)
	: name(name), heightMapGenerator(heightMapGenerator)
{
}

const TerrainChunk TerrainWorld::FetchChunkAt(glm::vec2 absoluteCoordinates)
{
	glm::ivec2 chunkCoordinates = { absoluteCoordinates.x / CHUNK_WIDTH, absoluteCoordinates.y / CHUNK_WIDTH };

	auto chunk = grid.FetchOne(chunkCoordinates);

	if (chunk.has_value()) {
		return chunk.value();
	}
	else {
		TerrainChunk newTerrainChunk = TerrainChunk(
			chunkCoordinates,
			{ CHUNK_WIDTH, CHUNK_WIDTH },
			heightMapGenerator.GenerateHeightMap(
				chunkCoordinates * CHUNK_WIDTH,
				{ CHUNK_WIDTH, CHUNK_WIDTH }
			)
		);

		grid.Insert(chunkCoordinates, newTerrainChunk);

		return newTerrainChunk;
	}
}

const std::vector<TerrainChunk> TerrainWorld::FetchChunksAt(glm::vec2 absoluteCoordinates, int radius)
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
					TerrainChunk newTerrainChunk = TerrainChunk(
						chunkCoordinates,
						{ CHUNK_WIDTH, CHUNK_WIDTH },
						heightMapGenerator.GenerateHeightMap(
							chunkCoordinates * CHUNK_WIDTH,
							{ CHUNK_WIDTH, CHUNK_WIDTH }
						)
					);

					grid.Insert(chunkCoordinates, newTerrainChunk);

					result.push_back(newTerrainChunk);
				}
			}
		}

		return result;
	}
}

const void TerrainWorld::GenerateChunkAt(glm::vec2 absoluteCoordinates)
{
	glm::ivec2 chunkCoordinates = { absoluteCoordinates.x / CHUNK_WIDTH, absoluteCoordinates.y / CHUNK_WIDTH };

	auto chunk = grid.FetchOne(chunkCoordinates);

	if (chunk.has_value()) {
		return;
	}
	else {
		TerrainChunk newTerrainChunk = TerrainChunk(
			chunkCoordinates,
			{ CHUNK_WIDTH, CHUNK_WIDTH },
			heightMapGenerator.GenerateHeightMap(
				chunkCoordinates * CHUNK_WIDTH,
				{ CHUNK_WIDTH, CHUNK_WIDTH }
			)
		);

		grid.Insert(chunkCoordinates, newTerrainChunk);
	}
}

const void TerrainWorld::GenerateChunksAt(glm::vec2 absoluteCoordinates, int radius)
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
					TerrainChunk newTerrainChunk = TerrainChunk(
						chunkCoordinates,
						{ CHUNK_WIDTH, CHUNK_WIDTH },
						heightMapGenerator.GenerateHeightMap(
							chunkCoordinates * CHUNK_WIDTH,
							{ CHUNK_WIDTH, CHUNK_WIDTH }
						)
					);

					grid.Insert(chunkCoordinates, newTerrainChunk);
				}
			}
		}
	}
}

const std::optional<TerrainChunk> TerrainWorld::FetchCachedChunkAt(glm::vec2 absoluteCoordinates) const
{
	return grid.FetchOne({ absoluteCoordinates.x / CHUNK_WIDTH, absoluteCoordinates.y / CHUNK_WIDTH });
}

const std::vector<TerrainChunk> TerrainWorld::FetchCachedChunksAt(glm::vec2 absoluteCoordinates, int radius) const
{
	return grid.Fetch({ absoluteCoordinates.x / CHUNK_WIDTH, absoluteCoordinates.y / CHUNK_WIDTH }, radius);
}
