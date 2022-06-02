#include "openvdb/openvdb.h"
#include "openvdb/tools/ParticlesToLevelSet.h"
#include <openvdb/tools/LevelSetUtil.h>

#include "VDBParticleSystemConverter.h"
#include "VDBPointsScene.h"
#include "VDBPointsImpl.h"
#include "VDBVolumeScene.h"
#include "VDBVolumeImpl.h"
#include "../../CrystalScene/Scene/ParticleSystemScene.h"

#include "Converter.h"

using namespace openvdb;
using namespace Crystal::Shape;
using namespace Crystal::VDB;
using namespace Crystal::Scene;

void VDBParticleSystemConverter::toVolume(const VDBPointsScene& particles, const float radius, const float voxelSize, VDBVolumeScene* volume)
{
    /*
    // Rasterize into an SDF.
    auto sdf = createLevelSet<FloatGrid>(voxelSize);
    sdf->setName("density");
    auto p = particles.getImpl();
    if (p->size() == 0) {
        return;
    }
    tools::particlesToSdf(*p, *sdf, radius);
    std::unique_ptr<VDBVolumeScene> v = std::make_unique<VDBVolumeScene>();
    volume->getImpl()->setPtr(sdf);
    */
}

void VDBParticleSystemConverter::fromVDB(const VDBPointsScene& src, ParticleSystemScene* ps)
{
    ps->clear();

    auto impl = src.getImpl();
    const auto count = impl->size();
    const auto positions = impl->getPositions();
    for (int i = 0; i < count; ++i) {
        openvdb::Real radius;
        const auto p = Converter::fromVDB(positions[i]);
        ParticleAttribute attr;
        attr.color = Crystal::Graphics::ColorRGBAf(0, 0, 0, 0);
        attr.size = radius;
        ps->getShape()->add(p, attr);
    }
}

void VDBParticleSystemConverter::toVDB(const IParticleSystemScene& src, VDBPointsScene* dest)
{
    dest->clear();
    const auto positions = src.getPositions();
    dest->create(positions);
}
