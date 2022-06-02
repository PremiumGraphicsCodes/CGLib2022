#include "Torus3d.h"

#include "Tolerance.h"

using namespace Crystal::Math;

Torus3d::Torus3d() :
	center(0, 0, 0),
	R(1.0),
	r(0.5)
{}

Torus3d::Torus3d(const Vector3dd& center, const double R, const double r) :
	center(center),
	R(R),
	r(r)
{}

Vector3dd Torus3d::getPosition(const double u, const double v) const
{
	const auto t = u * 2.0 * PI;
	const auto p = v * 2.0 * PI;
	const auto x = R * ::cos(t) + r * ::cos(p) * ::cos(t);
	const auto y = R * ::sin(t) + r * ::cos(p) * ::sin(t);
	const auto z = r * ::sin(p);
	return center + Vector3dd(x, y, z);
}

Vector3dd Torus3d::getNormal(const double u, const double v) const
{
	// todo.
	return Vector3dd();
}
