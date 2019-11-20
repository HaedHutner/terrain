#ifndef _MATERIALS_GENERATOR_H
#define _MATERIALS_GENERATOR_H

#include <Matrix.h>
#include <MatrixGenerator.h>

enum class Materials {
	Rock,
	Grass,
	Sand,
	Ice
};

class MaterialsGenerator : public MatrixGenerator {
private:

	Materials determineMaterial(const float &value);

public:

	MaterialsGenerator(const FastNoise::NoiseType& noiseType = FastNoise::NoiseType::PerlinFractal, const int& seed = 1337);

	tools::Matrix<int> GenerateMaterials(const tools::Matrix<float> &heightMap);

};

#endif