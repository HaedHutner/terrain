#ifndef _HEIGHT_MAP_GENERATOR_H
#define _HEIGHT_MAP_GENERATOR_H

#include <glm/glm.hpp>
#include <FastNoise/FastNoise.h>

#include <MatrixGenerator.h>
#include <Matrix.h>

class HeightMapGenerator : public MatrixGenerator {
public:

    HeightMapGenerator(const FastNoise::NoiseType &noiseType = FastNoise::NoiseType::PerlinFractal, const int &seed = 1337);

    tools::Matrix<float> GenerateHeightMap(const glm::ivec2 &startingPosition, const glm::ivec2 &sizeLimits, const float &startingHeight = 0.0f, const float &heightModifier = 1.0f);

};

#endif