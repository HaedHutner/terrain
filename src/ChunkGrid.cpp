#include <ChunkGrid.h>

ChunkGrid::ChunkGrid()
	: grid()
{
}

void ChunkGrid::Insert(glm::ivec2 chunkCoordinates, TerrainChunk chunk)
{
	grid[chunkCoordinates] = chunk;
}

const std::optional<TerrainChunk> ChunkGrid::FetchOne(glm::ivec2 chunkCoordinates) const
{
	if (grid.find(chunkCoordinates) != grid.end()) {
		return std::optional<TerrainChunk>{ grid.at(chunkCoordinates) };
	}
	else {
		return std::nullopt;
	}
}

const std::vector<TerrainChunk> ChunkGrid::Fetch(glm::ivec2 chunkCoordinates, int radius) const
{
	if (radius == 0) {
		try {
			return std::vector<TerrainChunk>{ grid.at(chunkCoordinates) };
		}
		catch (const std::out_of_range & e) {
			return std::vector<TerrainChunk>();
		}
	} else {
		std::vector<TerrainChunk> result = std::vector<TerrainChunk>();

		for (int i = -radius; i < radius; i++) {
			for (int j = -radius; j < radius; j++) {
				if (grid.find({ chunkCoordinates.x + i, chunkCoordinates.y + j }) != grid.end()) {
					result.push_back(grid.at({ chunkCoordinates.x + i, chunkCoordinates.y + j }));
				}
			}
		}

		return result;
	}
}
