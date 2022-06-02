#include "VDBVolumeToMeshConverter.h"
#include "VDBVolumeImpl.h"
#include "VDBMeshImpl.h"
#include "openvdb/tools/VolumeToMesh.h"

using namespace Crystal::VDB;

VDBMeshScene* VDBVolumeToMeshConverter::toMesh(const VDBVolumeScene& volume, const double threshold, const double adaptivity)
{
    VDBMeshScene* mesh = new VDBMeshScene();
    auto impl = mesh->getImpl();
    auto grid = volume.getImpl()->getPtr();
    std::vector<openvdb::Vec3I> triangles;
    std::vector<openvdb::Vec4I> quads;
    openvdb::tools::volumeToMesh(*grid, impl->points, triangles, quads, threshold, adaptivity);
    for (const auto& t : triangles) {
        Crystal::VDB::VDBMeshImpl::TriangleFace face;
        face.indices = t;
        impl->triangles.push_back(face);
    }
    for (const auto& q : quads) {
        Crystal::VDB::VDBMeshImpl::QuadFace face;
        face.indices = q;
        impl->quads.push_back(face);
    }
    impl->updateNormals();
    return mesh;
}
