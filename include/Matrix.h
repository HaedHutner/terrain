#ifndef _MATRIX_H
#define _MATRIX_H

#include <memory>
#include <vector>

namespace tools {
	template <typename T>
	using Matrix = std::vector<std::vector<T>>;

	template <typename T>
	Matrix<T> CreateMatrix(int width, int height, T initialValue) {
		return std::vector<std::vector<T>>(width, std::vector<T>(height, initialValue));
	}
}

#endif
