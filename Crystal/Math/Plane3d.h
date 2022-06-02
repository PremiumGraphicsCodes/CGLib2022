#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Plane3d
{
public:
	Plane3d();

	Plane3d(const Vector3dd& origin, const Vector3dd& normal);

	Plane3d(const double d, const Vector3dd& normal);

	Vector3dd getOrigin() const { return origin; }

	Vector3dd getNormal() const { return normal; }

	double getDistance(const Vector3dd& position) const;

	bool isSame(const Plane3d& rhs, const double tolerance) const;

	double calculateD() const;

private:
	Vector3dd origin;
	Vector3dd normal;
};

class Plane3dWithD
{

};

	}
}