#pragma once

#include "glm.h"

namespace Crystal {
	namespace Math {

template<typename T>
using Matrix4d = glm::mat<4, 4, T>;

using Matrix4df = Matrix4d<float>;
using Matrix4dd = Matrix4d<double>;

template<typename T>
static Matrix4d<T> Identity()
{
	return Matrix4d<T>
	(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

template<typename T>
static Matrix4d<T> operator*(const Matrix4d<T>& lhs, const Matrix4d<T>& rhs)
{
	Matrix4d<T> result(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				result[i][j] += lhs[i][k] * rhs[k][j];
			}
		}
	}
	return result;
}

	}
}