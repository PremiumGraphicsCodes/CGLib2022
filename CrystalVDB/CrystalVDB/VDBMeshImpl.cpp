#include "VDBMeshImpl.h"

using namespace Crystal::VDB;

namespace {
	openvdb::Vec3s getNormal(const std::vector<openvdb::Vec3s>& positions, const int p0, const int p1, const int p2)
	{
		const auto& v0 = positions[p0];
		const auto& v1 = positions[p1];
		const auto& v2 = positions[p2];
		auto v21 = openvdb::Vec3s(v2 - v1);
		v21.normalize();
		auto v01 = openvdb::Vec3d(v0 - v1);
		v01.normalize();
		const auto normal = v21.cross(v01);
		return normal;
	}
}

std::vector<openvdb::Vec3I> VDBMeshImpl::getTriangles() const
{
	std::vector<openvdb::Vec3I> results;
	for (const auto& q : triangles) {
		results.push_back(q.indices);
	}
	return results;
}

std::vector<openvdb::Vec4I> VDBMeshImpl::getQuads() const
{
	std::vector<openvdb::Vec4I> results;
	for (const auto& q : quads) {
		results.push_back(q.indices);
	}
	return results;
}

void VDBMeshImpl::updateNormals()
{
	for (auto& tt : triangles) {
		const auto& t = tt.indices;
		tt.normal = getNormal(points, t[0], t[1], t[2]);
	}
	for (auto& qq : quads) {
		const auto& q = qq.indices;
		qq.normal = getNormal(points, q[0], q[1], q[2]);
	}
}
