#pragma once

#include <cmath>
#include "glm.h"

namespace Crystal {
	namespace Math {

using Vector4df = glm::vec4;
using Vector4dd = glm::dvec4;

static double getDistanceSquared(const Vector4dd& v)
{
	return std::pow(v.x, 2) + std::pow(v.y, 2) + std::pow(v.z,2) + std::pow(v.w,2);
}

static double getDistanceSquared(const Vector4dd& lhs, const Vector4dd& rhs)
{
	return std::pow(lhs.x - rhs.x, 2) + std::pow(lhs.y - rhs.y, 2) + std::pow(lhs.z - rhs.z,2) + std::pow(lhs.w - rhs.w,2);
}

static bool areSame(const Vector4dd& lhs, const Vector4dd& rhs, const double tolerance)
{
	return getDistanceSquared(lhs, rhs) < tolerance;
}

	}
}
