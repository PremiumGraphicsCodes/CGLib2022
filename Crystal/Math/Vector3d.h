#pragma once

#include <cmath>
#include "glm.h"

namespace Crystal {
	namespace Math {

template<typename T>
using Vector3d = glm::vec<3, T>;

using Vector3df = Vector3d<float>;
using Vector3dd = Vector3d<double>;

template<typename T>
static T getLengthSquared(const Vector3d<T>& v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

template<typename T>
static T getLength(const Vector3d<T>& v)
{
	return std::sqrt(getLengthSquared(v));
}

template<typename T>
static T getDistanceSquared(const Vector3d<T>& v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

template<typename T>
static T getDistanceSquared(const Vector3d<T>& lhs, const Vector3d<T>& rhs)
{
	const auto x = lhs.x - rhs.x;
	const auto y = lhs.y - rhs.y;
	const auto z = lhs.z - rhs.z;
	return x * x + y * y + z * z;
}

template<typename T>
static T getDistance(const Vector3d<T>& lhs, const Vector3d<T>& rhs)
{
	return std::sqrt(getDistanceSquared(lhs, rhs));
}

template<typename T>
static bool areSame(const Vector3d<T>& lhs, const Vector3d<T>& rhs, const T tolerance)
{
	return getDistanceSquared(lhs, rhs) < tolerance;
}

	}
}