#pragma once

#include "Vector2d.h"

#include "Tolerance.h"

namespace Crystal {
	namespace Math {

class Circle2d
{
public:
	Circle2d() :
		Circle2d(1.0)
	{
	}

	explicit Circle2d(const double radius) :
		Circle2d(radius, Vector2dd(0,0))
	{
	}

	Circle2d(const double radius, const Vector2dd& center) :
		radius(radius),
		center(center)
	{}

	Vector2dd getPosition(const double u) const
	{
		const auto theta = u * 2.0 * PI;
		const auto x = radius * ::cos(theta);
		const auto y = radius * ::sin(theta);
		return center + Vector2dd(x, y);
	}

private:
	double radius;
	Vector2dd center;
};
	}
}