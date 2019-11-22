#include <HeightMapGenerator.h>

HeightMapGenerator::HeightMapGenerator(const FastNoise::NoiseType &noiseType, const int &seed) 
	: MatrixGenerator(noiseType, seed)
{
	fastNoise.SetNoiseType(FastNoise::NoiseType::PerlinFractal);
	fastNoise.SetFractalOctaves(5);
}

tools::Matrix<float> HeightMapGenerator::GenerateHeightMap(const glm::ivec2 &startingPosition, const glm::ivec2 &sizeLimits, const float &startingHeight, const float &heightModifier) {
	tools::Matrix<float> heightMap = tools::CreateMatrix(sizeLimits.x, sizeLimits.y, startingHeight);

    for (int x = 0; x < sizeLimits.x; x++) {
        for (int y = 0; y < sizeLimits.y; y++) {
            heightMap[x][y] = startingHeight + ( fastNoise.GetNoise(startingPosition.x + x, startingPosition.y + y) * heightModifier );
        }
    }

    return heightMap;
}
