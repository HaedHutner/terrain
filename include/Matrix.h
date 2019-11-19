#include <vector>

namespace tools {
	template <typename T>
	using Matrix = std::vector<std::vector<T>>;

	template <typename T>
	Matrix<T> create_matrix(int width, int height, T initialValue) {
		std::vector<std::vector<T>> matrix(width);
		
		for (int i = 0; i < height; i++) {
			matrix[i].resize(initialValue);
		}

		return matrix;
	}
}

