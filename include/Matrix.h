#include <vector>

namespace tools {
	template <typename T>
	using Matrix = std::vector<std::vector<T>>;

	template <typename T>
	Matrix<T> create_matrix(int width, int height, T initialValue) {
		return std::vector<std::vector<T>>(width, std::vector<T>(height, initialValue));
	}
}

