#include "VDBFileWriter.h"

#include <openvdb/points/PointConversion.h>

#include "VDBPointsScene.h"
#include "VDBPointsImpl.h"

#include "VDBVolumeScene.h"
#include "VDBVolumeImpl.h"

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

//openvdb::Vec3R

namespace {
    openvdb::io::File file("");
}

VDBFileWriter::~VDBFileWriter()
{
    close();
}

bool VDBFileWriter::open(const std::string& filePath)
{
    file = openvdb::io::File(filePath);
    return true;
}

void VDBFileWriter::close()
{
    file.close();
}

void VDBFileWriter::writePoints(const std::string& name, VDBPointsScene* points) const
{
    /*
    try {
        file.open();
    }
    catch (openvdb::Exception& e) {
        std::cout << "file could not open" << std::endl;
        return;
    }
    */

    auto grid = points->getImpl()->getPtr();

    /*
    std::vector<openvdb::Vec3s> ps = points->getImpl()->getPositions();//Converter::toVDB(positions);
    openvdb::points::PointAttributeVector<openvdb::Vec3s> positionsWrapper(ps);

    int pointsPerVoxel = 8;
    float voxelSize = openvdb::points::computeVoxelSize(positionsWrapper, pointsPerVoxel);

    auto transform = openvdb::math::Transform::createLinearTransform(voxelSize);
    auto grid = openvdb::points::createPointDataGrid
        <
        openvdb::points::NullCodec,
        openvdb::points::PointDataGrid
        >
        (ps, *transform);
    grid->setName(name);
    //std::cout << grid->gridType() << std::endl;
    */
    /*
    if (!file.isOpen()) {
        return false;
    }
    */
    file.write({ grid });
}

void VDBFileWriter::writeVolumes(const std::vector<VDBVolumeScene*>& volumes) const
{
    openvdb::GridCPtrVec ptrs;
    for (auto v : volumes) {
        ptrs.push_back(v->getImpl()->getPtr());
    }
    file.write(ptrs);
}
