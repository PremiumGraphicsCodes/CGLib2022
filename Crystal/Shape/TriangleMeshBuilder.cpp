#include "TriangleMeshBuilder.h"

#include "../Math/Quad3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

namespace {
	constexpr auto tolerance = 1.0e-12;
}

TriangleMeshBuilder::TriangleMeshBuilder()
{
}

void TriangleMeshBuilder::add(const Triangle3d& triangle)
{
	faces.push_back(TriangleFace(triangle));
}

void TriangleMeshBuilder::add(const Quad3d& quad)
{
	const auto p0 = quad.getPosition(0.0, 0.0);
	const auto p1 = quad.getPosition(1.0, 0.0);
	const auto p2 = quad.getPosition(0.0, 1.0);
	const auto p3 = quad.getPosition(1.0, 1.0);

	const Triangle3d t1(p0, p1, p2);
	const TriangleFace f1(t1);

	const Triangle3d t2(p3, p2, p1);
	const TriangleFace f2(t2);

	faces.push_back(f1);
	faces.push_back(f2);
}

std::unique_ptr<TriangleMesh> TriangleMeshBuilder::build()
{
	auto mesh = std::make_unique<TriangleMesh>();
	for (const auto& f : faces) {
		mesh->addFace(f);
	}
	return std::move(mesh);
}

void TriangleMeshBuilder::add(const ISurface3dd& surface, const int unum, const int vnum)
{
	const auto du = 1.0 / static_cast<double>(unum);
	const auto dv = 1.0 / static_cast<double>(vnum);

	std::vector<std::vector<Vector3dd>> positions;

	for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
		std::vector<Vector3dd> ps;

		for (auto v = 0.0; v < 1.0 + tolerance; v += du) {
			ps.push_back(surface.getPosition(u, v));
		}
		positions.push_back(ps);
	}

	for (int i = 0; i < unum; ++i) {
		for (int j = 0; j < vnum; ++j) {
			const Triangle3d t1(positions[i][j], positions[i+1][j], positions[i][j+1]);
			faces.push_back(TriangleFace(t1));
			const Triangle3d t2(positions[i+1][j+1], positions[i][j+1], positions[i+1][j]);
			faces.push_back(TriangleFace(t2));
		}
	}
}

void TriangleMeshBuilder::add(const IVolume3dd& volume, const int unum, const int vnum, const int wnum)
{
	const auto v0 = volume.getPosition(0, 0, 0);
	const auto v1 = volume.getPosition(1, 0, 0);
	const auto v2 = volume.getPosition(1, 1, 0);
	const auto v3 = volume.getPosition(0, 1, 0);

	const auto v4 = volume.getPosition(0, 0, 1);
	const auto v5 = volume.getPosition(1, 0, 1);
	const auto v6 = volume.getPosition(1, 1, 1);
	const auto v7 = volume.getPosition(0, 1, 1);

	addFace(v0, v1, v2); // front
	addFace(v2, v3, v0);

	addFace(v1, v5, v6); // right
	addFace(v6, v2, v1);

	addFace(v6, v5, v4); // left
	addFace(v4, v7, v6);

	addFace(v4, v0, v3); // back
	addFace(v7, v4, v3);

	addFace(v6, v3, v2); // top;
	addFace(v7, v3, v6);

	addFace(v0, v5, v1); // bottom
	addFace(v0, v4, v5);
}

void TriangleMeshBuilder::addFace(const Vector3dd& v0, const Vector3dd& v1, const Vector3dd& v2)
{
	addFace(Triangle3d(v0, v1, v2));
}

void TriangleMeshBuilder::addFace(const Triangle3d& triangle)
{
	const TriangleFace f(triangle);
	faces.push_back(f);
}
