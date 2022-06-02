#include "PolygonMesh.h"

#include "../Math/Vector3d.h"

#include "../Shape/Vertex.h"
#include "../Shape/Face.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

PolygonMesh::PolygonMesh()
{}

PolygonMesh::~PolygonMesh()
{
	clear();
}

void PolygonMesh::clear()
{
	vertices.clear();
	faces.clear();
}

std::vector<Vertex> PolygonMesh::getVertices() const
{
	return vertices;
}

Vector3dd PolygonMesh::getCenter() const
{
	Vector3dd center(0,0,0);
	const auto& vs = this->getVertices();
	for (const auto& v : vs) {
		const auto p = positions[v.positionId];
		center += p / static_cast<double>(vs.size());
	}
	return center;
}

void PolygonMesh::move(const Vector3dd& vec)
{
	const auto& vs = this->getVertices();
	for (const auto& v : vs) {
		positions[v.positionId] += vec;
	}
}

void PolygonMesh::transform(const Matrix3dd& m)
{
	const auto& vs = vertices;
	for (auto v : vs) {
		auto& p = positions[v.positionId];
		p = m * p;
	}
}

void PolygonMesh::transform(const Matrix4dd& m)
{
	const auto& vs = vertices;
	for (auto v : vs) {
		auto& p = positions[v.positionId];
		p = m * glm::vec4(p, 1.0);
	}
}

Box3dd PolygonMesh::getBoundingBox() const
{
	const auto& vertices = getVertices();

	if (vertices.empty()) {
		return Box3dd();
	}

	Box3dd bb(positions.front());
	for (const auto& p : positions) {
		bb.add(p);
	}
	return bb;
}

