#include "Cylinder3d.h"

#include "Tolerance.h"

using namespace Crystal::Math;

Cylinder3d::Cylinder3d() :
	Cylinder3d(1.0)
{
}

Cylinder3d::Cylinder3d(const double radius) :
	Cylinder3d(radius, 1.0)
{
}

Cylinder3d::Cylinder3d(const double radius, const double height) :
	Cylinder3d(radius, height, Vector3dd(0, 0, 0))
{
}

Cylinder3d::Cylinder3d(const double radius, const double height, const Vector3dd& center) :
	radius(radius),
	height(height),
	center(center)
{
}

Vector3dd Cylinder3d::getPosition(const double u, const double v) const
{
	return getPosition(u, v, 1.0);
}

Vector3dd Cylinder3d::getPosition(const double r, const double h, const double w) const
{
	const auto theta = r * 2.0 * PI;
	const auto x = w * radius * ::cos(theta);
	const auto y = w * radius * ::sin(theta);
	const auto z = height * h - height * 0.5;
	return center + Vector3dd(x, y, z);
}

Vector3dd Cylinder3d::getNormal(const double u, const double v) const
{
	const auto c = getPosition(u, v, 0.0);
	const auto s = getPosition(u, v, 1.0);
	return glm::normalize(c - s);
}

bool Cylinder3d::isInside(const Vector3dd& position) const
{
	assert(false);
	return false;
}
