#pragma once

#include <cmath>

namespace Crystal {
	namespace Math {

constexpr double PI = 3.141592653589793238462643383279;

static bool isEqual(const double x, const double y, const double tolerance) { return ::fabs(x - y) < tolerance; }

	}
}