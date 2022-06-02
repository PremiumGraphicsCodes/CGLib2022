#include "PolygonMeshBuilder.h"

#include "../Math/Triangle3d.h"
#include "../Math/Plane3d.h"
#include "../Math/Quad3d.h"

#include "CircularBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

PolygonMeshBuilder::PolygonMeshBuilder() :
	nextVertexId(0),
	nextFaceId(0)
{}

void PolygonMeshBuilder::add(const Triangle3d& triangle)
{
	const auto& vs = triangle.getVertices();
	const auto p0 = createPosition(vs[0]);
	const auto p1 = createPosition(vs[1]);
	const auto p2 = createPosition(vs[2]);
	const auto n = createNormal(triangle.getNormal());
	const auto v0 = createVertex(p0, n, -1);
	const auto v1 = createVertex(p1, n, -1);
	const auto v2 = createVertex(p2, n, -1);
	createFace(v0, v1, v2);
}

namespace {
	constexpr auto tolerance = 1.0e-12;
}

void PolygonMeshBuilder::add(const ISurface3dd& surface, const int unum, const int vnum)
{
	const auto du = 1.0 / static_cast<double>(unum);
	const auto dv = 1.0 / static_cast<double>(vnum);

	std::vector<std::vector<int>> positions;
	std::vector<std::vector<int>> normals;
	std::vector<std::vector<int>> texCoords;

	for (auto u = 0.0; u < 1.0 + tolerance; u+=du) {
		std::vector<int> ps;
		std::vector<int> ns;
		std::vector<int> ts;

		for (auto v = 0.0; v < 1.0 + tolerance; v+=du) {
			ps.push_back( createPosition(surface.getPosition( u, v )) );
			ns.push_back( createNormal(surface.getNormal(u, v)) );
			ts.push_back( createTexCoord(Vector2dd(u, v)) );
		}
		positions.push_back(ps);
		normals.push_back(ns);
		texCoords.push_back(ts);
	}

	std::vector<std::vector<int>> vertices;
	for (int i = 0; i < positions.size(); ++i) {
		std::vector<int> vs;
		for (int j = 0; j < positions[i].size(); ++j) {
			vs.push_back( createVertex(positions[i][j], normals[i][j], texCoords[i][j]) );
		}
		vertices.push_back(vs);
	}

	for (int i = 0; i < unum; ++i) {
		for (int j = 0; j < vnum; ++j) {
			createFace(vertices[i][j], vertices[i+1][j], vertices[i][j+1]);
			createFace(vertices[i+1][j+1], vertices[i][j+1], vertices[i+1][j]);
		}
	}
}

void PolygonMeshBuilder::add(const IVolume3dd& volume, const int unum, const int vnun, const int wnum)
{
	auto p0 = createPosition(volume.getPosition(0, 0, 0));
	auto p1 = createPosition(volume.getPosition(1, 0, 0));
	auto p2 = createPosition(volume.getPosition(1, 1, 0));
	auto p3 = createPosition(volume.getPosition(0, 1, 0));

	auto p4 = createPosition(volume.getPosition(0, 0, 1));
	auto p5 = createPosition(volume.getPosition(1, 0, 1));
	auto p6 = createPosition(volume.getPosition(1, 1, 1));
	auto p7 = createPosition(volume.getPosition(0, 1, 1));

	auto n0 = createNormal(Vector3dd(1, 0, 0));
	auto n1 = createNormal(Vector3dd(-1, 0, 0));
	auto n2 = createNormal(Vector3dd(0, 1, 0));
	auto n3 = createNormal(Vector3dd(0, -1, 0));
	auto n4 = createNormal(Vector3dd(0, 0, 1));
	auto n5 = createNormal(Vector3dd(0, 0, -1));

	/*
	auto t0 = createTexCoord(Vector2dd(0, 0));
	auto t1 = createTexCoord(Vector2dd(1, 0));
	auto t2 = createTexCoord(Vector2dd(1, 1));
	auto t3 = createTexCoord(Vector2dd(0, 1));

	auto t4 = createTexCoord(Vector2dd(0, 0));
	auto t5 = createTexCoord(Vector2dd(1, 0));
	auto t6 = createTexCoord(Vector2dd(1, 1));
	auto t7 = createTexCoord(Vector2dd(0, 1));

	auto t8 = createTexCoord(Vector2dd(0, 0));
	auto t9 = createTexCoord(Vector2dd(1, 0));
	auto t10 = createTexCoord(Vector2dd(1, 1));
	auto t11 = createTexCoord(Vector2dd(0, 1));

	auto t12 = createTexCoord(Vector2dd(0, 0));
	auto t13 = createTexCoord(Vector2dd(1, 0));
	auto t14 = createTexCoord(Vector2dd(1, 1));
	auto t15 = createTexCoord(Vector2dd(0, 1));
	*/

	auto v0 = createVertex(p0, n5);
	auto v1 = createVertex(p1, n5);
	auto v2 = createVertex(p2, n5);
	auto v3 = createVertex(p3, n5);
	auto v4 = createVertex(p4, n4);
	auto v5 = createVertex(p5, n4);
	auto v6 = createVertex(p6, n4);
	auto v7 = createVertex(p7, n4);

	createFace(v0, v1, v2); // front
	createFace(v2, v3, v0);

	createFace(v1, v5, v6); // right
	createFace(v6, v2, v1);

	createFace(v6, v5, v4); // left
	createFace(v4, v7, v6);

	createFace(v4, v0, v3); // back
	createFace(v7, v4, v3);

	createFace(v6, v3, v2); // top;
	createFace(v7, v3, v6);

	createFace(v0, v5, v1); // bottom
	createFace(v0, v4, v5);
}

std::unique_ptr<PolygonMesh> PolygonMeshBuilder::build()
{
	auto mesh = std::make_unique<PolygonMesh>();
	mesh->positions = positions;
	mesh->normals = normals;
	mesh->texCoords = texCoords;
	mesh->vertices = vertices;
	mesh->faces = faces;
	return std::move(mesh);
}

void PolygonMeshBuilder::add(const int v0, const int v1, const int v2, const int v3)
{
	const auto& p0 = positions[v0];
	const auto& p1 = positions[v1];
	const auto& p2 = positions[v2];

	const auto& normal = glm::cross(p1 - p0, p2 - p0);
	auto n0 = createNormal(normal);

	auto vv0 = createVertex(v0, n0);
	auto vv1 = createVertex(v1, n0);
	auto vv2 = createVertex(v2, n0);
	auto vv3 = createVertex(v3, n0);

	createFace(vv0, vv1, vv2);
	createFace(vv0, vv2, vv3);
}

Vector3dd PolygonMeshBuilder::calculateNormal(const int v0, const int v1, const int v2)
{
	const auto& p0 = positions[v0];
	const auto& p1 = positions[v1];
	const auto& p2 = positions[v2];

	return glm::normalize( glm::cross(p1 - p0, p2 - p0) );
}

int PolygonMeshBuilder::createPosition(const Vector3dd& v)
{
	positions.push_back(v);
	return static_cast<int>(positions.size() - 1);
}

int PolygonMeshBuilder::createNormal(const Vector3dd& v)
{
	normals.push_back(v);
	return static_cast<int>(normals.size() - 1);
}

int PolygonMeshBuilder::createTexCoord(const Vector2dd& v)
{
	texCoords.push_back(v);
	return static_cast<int>(texCoords.size() - 1);
}

int PolygonMeshBuilder::createVertex(const int positionId, const int normalId, const int texCoordId)
{
	Vertex v;
	v.positionId = positionId;
	v.normalId = normalId;
	v.texCoordId = texCoordId;
	v.id = nextVertexId++;
	vertices.push_back(v);
	return v.id;
}

int PolygonMeshBuilder::createFace(int v0, int v1, int v2)
{
	Face f(v0, v1, v2, nextFaceId++);
	faces.push_back(f);
	return f.getId();
}
