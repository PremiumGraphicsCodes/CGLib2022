#include "DistanceCalculator.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

double DistanceCalculator::getDistance(const Triangle3d& triangle, const Vector3dd& position)
{
	const auto& n = triangle.getNormal();
	const auto origin = triangle.getVertices()[0];
	const auto v = position - origin;
	return glm::dot(n, v);
}
