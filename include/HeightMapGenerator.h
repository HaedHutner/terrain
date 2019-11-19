#include <glm/glm.hpp>
#include <FastNoise/FastNoise.h>

#include <Matrix.h>

class HeightMapGenerator {
private:

    FastNoise* fastNoise;

public:

    HeightMapGenerator(const FastNoise::NoiseType &noiseType = FastNoise::NoiseType::PerlinFractal, const int &seed = 1337);

    tools::Matrix<float> generateHeightMap(const glm::ivec2 &startingPosition, const glm::ivec2 &sizeLimits, const float &startingHeight = 0.0f, const float &heightModifier = 1.0f);

    ~HeightMapGenerator();
};