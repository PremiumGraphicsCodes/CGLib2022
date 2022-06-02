#include "Face.h"

#include "../Math/Triangle3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

Triangle3d Face::toTriangle(const std::vector<Vector3dd>& positions) const
{
	const auto& p1 = positions[vertexIds[0]];
	const auto& p2 = positions[vertexIds[1]];
	const auto& p3 = positions[vertexIds[2]];
	return Triangle3d({ p1, p2, p3 });
}

std::vector<Line3dd> Face::toLines(const std::vector<Vector3dd>& positions) const
{
	const auto& p1 = positions[vertexIds[0]];
	const auto& p2 = positions[vertexIds[1]];
	const auto& p3 = positions[vertexIds[2]];

	return { Line3dd(p1, p2 - p1), Line3dd(p2, p3 - p2), Line3dd(p3, p1 - p3) };
}
