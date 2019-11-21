#ifndef _MATRIX_GENERATOR_H
#define _MATRIX_GENERATOR_H

#include <FastNoise/FastNoise.h>

class MatrixGenerator {

protected:

	FastNoise fastNoise;

public:

	MatrixGenerator(const FastNoise::NoiseType &noiseType = FastNoise::NoiseType::PerlinFractal, const int &seed = 1337);

};

#endif