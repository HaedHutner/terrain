#include <HeightMapGenerator.h>

float HeightMapGenerator::GetHeight(glm::vec2 position)
{
	// return fastNoise.GetCellular(position.x, position.y);
	return fastNoise.GetCellular(position.x * 0.5f, position.y * 0.5f) * fastNoise.GetPerlinFractal(position.x * 0.5f, position.y * 0.5f);
}

HeightMapGenerator::HeightMapGenerator(const FastNoise::NoiseType &noiseType, const int &seed)
	: MatrixGenerator(noiseType, seed)
{
	fastNoise.SetNoiseType(FastNoise::NoiseType::PerlinFractal);
	fastNoise.SetFractalType(FastNoise::FractalType::FBM);
	fastNoise.SetFractalOctaves(7);

	fastNoise.SetCellularDistanceFunction(FastNoise::CellularDistanceFunction::Euclidean);
	fastNoise.SetCellularReturnType(FastNoise::CellularReturnType::Distance2Add);
	fastNoise.SetFrequency(0.004f);
	fastNoise.SetInterp(FastNoise::Interp::Quintic);
}

tools::Matrix<float> HeightMapGenerator::GenerateHeightMap(const glm::ivec2 &startingPosition, const glm::ivec2 &sizeLimits, const float &startingHeight, const float &heightModifier) {
	tools::Matrix<float> heightMap = tools::CreateMatrix(sizeLimits.x, sizeLimits.y, startingHeight);

    for (int x = 0; x < sizeLimits.x; x++) {
        for (int y = 0; y < sizeLimits.y; y++) {
			heightMap[x][y] = startingHeight + (GetHeight({ startingPosition.x + x - 1, startingPosition.y + y - 1 }) * heightModifier);
        }
    }

    return heightMap;
}
