#include <glm/glm.hpp>
#include <FastNoise/FastNoise.h>

#include <FloatMatrix.h>

class HeightMapGenerator {
private:

    FastNoise* fastNoise;

public:

    HeightMapGenerator(const FastNoise::NoiseType &noiseType = FastNoise::NoiseType::PerlinFractal, const int &seed = 1337);

    FloatMatrix generateHeightMap(const glm::ivec2 &startingPosition, const glm::ivec2 &sizeLimits, const glm::fvec2 &heightLimits);

    ~HeightMapGenerator();
};