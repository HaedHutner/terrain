#include <MatrixGenerator.h>

MatrixGenerator::MatrixGenerator(const FastNoise::NoiseType& noiseType, const int& seed) {
	fastNoise = new FastNoise();
	fastNoise->SetSeed(seed);
	fastNoise->SetNoiseType(noiseType);
}

MatrixGenerator::~MatrixGenerator() {
	delete fastNoise;
}