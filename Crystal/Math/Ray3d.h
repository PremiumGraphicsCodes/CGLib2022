#pragma once

#include "Vector3d.h"
#include "Line3d.h"

namespace Crystal {
	namespace Math {

class Ray3d
{
public:
	Ray3d() :
		origin(0,0,0),
		direction(1,0,0)
	{
	}

	Ray3d(const Vector3dd& origin, const Vector3dd& direction) :
		origin(origin),
		direction(direction)
	{
	}

	Vector3dd getOrigin() const { return origin; }

	Vector3dd getDirection() const { return direction; }

	Vector3dd getPosition(const double param) const { return origin + direction * param; }

	Line3dd toLine(const double length) const;

	bool isSame(const Ray3d& rhs, const double tolerance) const;

private:
	Vector3dd origin;
	Vector3dd direction;
};

	}
}