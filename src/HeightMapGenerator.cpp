#include <HeightMapGenerator.h>

HeightMapGenerator::HeightMapGenerator(const FastNoise::NoiseType &noiseType, const int &seed) {
    fastNoise = new FastNoise();
    fastNoise->SetSeed(seed);
    fastNoise->SetNoiseType(noiseType);
}

FloatMatrix HeightMapGenerator::generateHeightMap(const glm::ivec2 &startingPosition, const glm::ivec2 &sizeLimits, const glm::fvec2 &heightLimits) {
    FloatMatrix heightMap = FloatMatrix(sizeLimits.x, sizeLimits.y, heightLimits.x);

    for (int x = 0; x < sizeLimits.x; x++) {
        for (int y = 0; y < sizeLimits.y; y++) {
            heightMap.set(x, y, heightLimits.x + ( fastNoise->GetNoise(startingPosition.x + x, startingPosition.y + y) * heightLimits.y ) );
        }
    }

    return heightMap;
}

HeightMapGenerator::~HeightMapGenerator() {
    delete fastNoise;
}