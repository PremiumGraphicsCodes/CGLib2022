#include "VDBFileReader.h"

#include "Converter.h"

#include <openvdb/points/PointConversion.h>

#include "VDBPointsScene.h"
#include "VDBPointsImpl.h"

#include "VDBVolumeScene.h"
#include "VDBVolumeImpl.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

namespace {
    openvdb::io::File file("");
}

VDBFileReader::~VDBFileReader()
{
    if (file.isOpen()) {
        close();
    }
}

bool VDBFileReader::open(const std::string& filename)
{
    file = openvdb::io::File(filename);
    const auto isOk = file.open();
    return isOk;
}

void VDBFileReader::close()
{
    file.close();
}

void VDBFileReader::readMetaData()
{
    auto metas = file.readAllGridMetadata();
    for (auto iter = metas->begin(); iter != metas->end(); ++iter) {
        const auto isPoint = (*iter)->isType<openvdb::points::PointDataGrid>();
        if (isPoint) {
            //std::cout << (*iter)->getName() << std::endl;
            pointNames.push_back((*iter)->getName());
            continue;
        }
        const auto isVolume = (*iter)->isType<openvdb::FloatGrid>();
        if (isVolume) {
            floatGridNames.push_back((*iter)->getName());
        }
    }
}

VDBPointsScene* VDBFileReader::readPositions(const std::string& pointName, const float radius)
{
    auto baseGrid = file.readGrid(pointName);

    auto grid = openvdb::gridPtrCast<openvdb::points::PointDataGrid>(baseGrid);
    auto count = openvdb::points::pointCount(grid->tree());
    //std::cout << "PointCount=" << count << std::endl;

    std::vector<openvdb::Vec3R> v_positions;
    std::vector<openvdb::Index32> v_indices;

    VDBPointsScene* psScene = new VDBPointsScene();
    psScene->getImpl()->setPtr(grid);

    return psScene;
}

VDBVolumeScene* VDBFileReader::readVolume(const std::string& volumeName)
{
    auto grid = openvdb::gridPtrCast<openvdb::FloatGrid>( file.readGrid(volumeName) );
    //auto impl = new VDBVolumeImpl( grid );
    auto scene = new VDBVolumeScene();
    scene->getImpl()->setPtr(grid);
    return scene;
}