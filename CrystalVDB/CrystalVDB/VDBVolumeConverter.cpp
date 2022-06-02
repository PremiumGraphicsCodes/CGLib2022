#include "VDBVolumeConverter.h"

#include <openvdb/openvdb.h>

#include <openvdb/points/PointSample.h>
#include <openvdb/tools/LevelSetUtil.h>


#include "openvdb/tools/VolumeToMesh.h"

#include "VDBVolumeScene.h"
#include "VDBVolumeImpl.h"
#include "Converter.h"

#include "CrystalSpace/CrystalSpace/SparseVolume.h"

using namespace Crystal::Space;
using namespace Crystal::Scene;
using namespace Crystal::VDB;


void VDBVolumeConverter::fromSparseVolume(const SparseVolume<float>& sp, VDBVolumeScene* volume) const
{
    const auto length = sp.getCellLength();
    Crystal::Math::Matrix4dd matrix
    (
        length[0], 0.0, 0.0, 0.0,
        0.0, length[1], 0.0, 0.0,
        0.0, 0.0, length[2], 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    volume->getImpl()->setTransformMatrix(matrix);
    auto& accesor = volume->getImpl()->getPtr()->getAccessor();
    const auto bb = sp.getBoundingBox();
    const auto nodes = sp.getNodes();
    for (auto n : nodes) {
        const auto ix = n->getIndex();
        openvdb::math::Coord c(ix[0], ix[1], ix[2]);
        accesor.setValue(c, n->getValue());
    }
    //Converter::toVDB()
    //volume->getImpl()->getPtr()->
    //volume->setValue()
}
