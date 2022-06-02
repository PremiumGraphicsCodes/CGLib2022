#include "Plane3d.h"

using namespace Crystal::Math;

Plane3d::Plane3d() :
	origin(0, 0, 0),
	normal(0, 0, 1)
{
}

Plane3d::Plane3d(const Vector3dd& origin, const Vector3dd& normal) :
	origin(origin),
	normal(normal)
{
}

Plane3d::Plane3d(const double d, const Vector3dd& normal) :
	normal(normal)
{
	origin = d * normal;
}

double Plane3d::getDistance(const Vector3dd& position) const
{
	const auto& v = position - origin;
	return glm::dot(v, normal);
}

bool Plane3d::isSame(const Plane3d& rhs, const double tolerance) const
{
	return
		areSame(origin, rhs.origin, tolerance) &&
		areSame(normal, rhs.normal, tolerance);
}

double Plane3d::calculateD() const
{
	return glm::dot(origin, normal);
}
