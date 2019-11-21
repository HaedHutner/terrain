#include <MatrixGenerator.h>

MatrixGenerator::MatrixGenerator(const FastNoise::NoiseType& noiseType, const int& seed) 
	: fastNoise(seed)
{
	fastNoise.SetNoiseType(noiseType);
}