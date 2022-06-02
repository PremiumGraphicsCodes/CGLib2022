#include "Overlap.h"

#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Math/Plane3d.h"
#include "../../Crystal/Math/Triangle3d.h"

//#include "../ThirdParty/tribox/tribox2.cpp"
#include "TriangleBoxOverlapCalculator.h"

#include <array>

using namespace Crystal::Math;
using namespace Crystal::Space;

bool Overlap::overlap(const Box3dd& box, const Plane3d& plane, const double tolerance)
{
	// https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plane.html

	// Convert AABB to center-extents representation
	const auto c = box.getCenter(); // Compute AABB center
	const auto e = box.getMax() - c; // Compute positive extents

	const auto n = plane.getNormal();

	// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
	auto r = e[0] * ::fabs(n[0]) + e[1] * ::fabs(n[1]) + e[2] * ::fabs(n[2]);

	const auto d = plane.calculateD();

	// Compute distance of box center from plane
	auto s = glm::dot(n, c) - d;

	// Intersection occurs when distance s falls within [-r,+r] interval
	return ::fabs(s) <= r;
}

bool Overlap::overlap(const Box3dd& box, const Triangle3d& triangle)
{
	const auto c = box.getCenter();
	std::array<double, 3> boxCenter{ c.x, c.y, c.z };

	const auto hs = box.getLength() * 0.5;
	std::array<double, 3> halfSize{ hs.x, hs.y, hs.z };

	const auto vs = triangle.getVertices();
	double vertices[3][3];
	for (int i = 0; i < 3; ++i) {
		vertices[i][0] = vs[i].x;
		vertices[i][1] = vs[i].y;
		vertices[i][2] = vs[i].z;
	}
	auto retCode = TriangleBoxOverlapCalculator::triBoxOverlap(boxCenter.data(), halfSize.data(), vertices);
	return (retCode == 1);
}
