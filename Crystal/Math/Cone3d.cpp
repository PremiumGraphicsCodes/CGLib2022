#include "Cone3d.h"

#include "Tolerance.h"

using namespace Crystal::Math;

Cone3d::Cone3d() :
	bottom(0, 0, 0),
	radius(1.0),
	height(1.0)
{}

Cone3d::Cone3d(const Vector3dd& bottom, const double radius, const double height) :
	bottom(bottom),
	radius(radius),
	height(height)
{
}

Vector3dd Cone3d::getPosition(const double u, const double v) const
{
	const auto uu = u * 2.0 * PI;
	const auto r = radius * (1.0 - v);
	const auto x = r * ::cos(uu);
	const auto y = r * ::sin(uu);
	const auto z = v * height;
	return bottom + Vector3dd(x, y, z);
}

Vector3dd Cone3d::getPosition(const double u, const double v, const double w) const
{
	const auto uu = u * 2.0 * PI;
	const auto r = w * radius * (1.0 - v);
	const auto x = r * ::cos(uu);
	const auto y = r * ::sin(uu);
	const auto z = v * height;
	return bottom + Vector3dd(x, y, z);
}

Vector3dd Cone3d::getNormal(const double u, const double v) const
{
	const auto dx = 1.0e-3;
	const auto v0 = getPosition(u, v);
	const auto v1 = getPosition(u + dx, v);
	const auto v2 = getPosition(u, v + dx);
	return glm::cross(v1 - v0, v2 - v0);
}

bool Cone3d::isInside(const Vector3dd& position) const
{
	assert(false);
	return false;
}
