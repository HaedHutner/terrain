#include <MaterialsGenerator.h>

MaterialsGenerator::MaterialsGenerator(const FastNoise::NoiseType& noiseType, const int& seed)
	: MatrixGenerator(noiseType, seed)
{
}

tools::Matrix<int> MaterialsGenerator::GenerateMaterials(const tools::Matrix<float>& heightMap) {
	tools::Matrix<int> materialsMap = tools::CreateMatrix(heightMap.size(), heightMap[0].size(), 0);

	for (int i = 0; i < heightMap.size(); i++) {
		for (int j = 0; j < heightMap[0].size(); j++) {
			materialsMap[i][j] = int(determineMaterial(heightMap[i][j]));
		}
	}

	return materialsMap;
}

Materials MaterialsGenerator::determineMaterial(const float& value)
{
	if (value < 0.0) return Materials::Sand;
	if (value < 0.25) return Materials::Grass;
	if (value < 0.75) return Materials::Rock;
	if (value >= 0.75) return Materials::Ice;

	return Materials::Rock;
}