#include <openvdb/tools/MeshToVolume.h>

#include "VDBMeshToVolumeConverter.h"

#include "CrystalVDB/CrystalVDB/VDBMeshScene.h"
#include "CrystalVDB/CrystalVDB/VDBMeshImpl.h"
#include "CrystalVDB/CrystalVDB/VDBVolumeScene.h"
#include "CrystalVDB/CrystalVDB/VDBVolumeImpl.h"

using namespace Crystal::VDB;

VDBVolumeScene* VDBMeshToVolumeConverter::toVolume(const VDBMeshScene& mesh, const double divideLength)
{
	const auto scale = 1.0 / divideLength;
	openvdb::math::Transform::Ptr xform = openvdb::math::Transform::createLinearTransform(divideLength);
	const auto triangles = mesh.getImpl()->getTriangles();
	const auto quads = mesh.getImpl()->getQuads();
	std::vector<openvdb::Vec3s> points = mesh.getImpl()->points;
	for (auto& p : points) {
		p *= scale;
	}
	openvdb::tools::QuadAndTriangleDataAdapter<openvdb::Vec3s, openvdb::Vec3I> m1(points, triangles);
	//openvdb::tools::QuadAndTriangleDataAdapter<openvdb::Vec3s, openvdb::Vec4I> m2(points, quads);
	auto result = openvdb::tools::meshToVolume<openvdb::FloatGrid>(m1, *xform);
	auto volume = new VDBVolumeScene();
	volume->getImpl()->setPtr(result);
	return volume;
	/*
	auto impl = new VDBVolumeImpl(result);
	//impl->setScale(1.0 / divideLength);
	delete volume->getImpl();
	volume->setImpl(impl);
	*/
}
