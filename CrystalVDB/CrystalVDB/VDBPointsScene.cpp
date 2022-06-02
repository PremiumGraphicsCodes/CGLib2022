#include "VDBPointsScene.h"

#include "VDBPointsImpl.h"

#include "Converter.h"

#include <openvdb/points/PointConversion.h>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBPointsScene::VDBPointsScene() :
    VDBPointsScene(-1, "")
{}

VDBPointsScene::VDBPointsScene(const int id, const std::string name) :
    IParticleSystemScene(id, name)
{
    this->impl = std::make_unique<VDBPointsImpl>();
    this->presenter = std::make_unique<VDBPointsPresenter>(this);
}

VDBPointsScene::~VDBPointsScene()
{
}

void VDBPointsScene::create(const std::vector<Vector3dd>& positions)
{
    std::vector<openvdb::Vec3f> coords;
    for (const auto& p : positions) {
        coords.push_back(Converter::toVDB(p));
    }

    const auto transform = openvdb::math::Transform::createLinearTransform();
    //auto ptr = openvdb::points::createPointDataGrid<openvdb::points::NullCodec, openvdb::points::PointDataGrid>(coords, transform);
    auto ptr = openvdb::points::createPointDataGrid<openvdb::points::NullCodec, openvdb::points::PointDataGrid>(coords, *transform);

    impl->setPtr(ptr);
    //this->impl->setPtr()
}

/*
void VDBParticleSystemScene::fromCrystal(const std::vector<Vector3dd>& positions, const float radius)
{
    for (const auto& p : positions) {
        this->add(p, radius);
    }
}
*/

Box3dd VDBPointsScene::getBoundingBox() const
{
    const auto size = impl->size();
    if (size == 0) {
        return Box3dd::createDegeneratedBox();
    }
    const auto positions = getPositions();
    Box3dd box(positions.front());
    for (int i = 0; i < size; ++i) {
        box.add(positions[i]);
    }
    return box;
}

std::vector<Vector3dd> VDBPointsScene::getPositions() const
{
    std::vector<Vector3dd> positions;
    const auto ps = impl->getPositions();
    for (int i = 0; i < impl->size(); ++i) {
        positions.emplace_back( Converter::fromVDB(ps[i]) );
    }
    return positions;
}

void VDBPointsScene::resetImpl()
{
    this->impl = std::make_unique<VDBPointsImpl>();
}

void VDBPointsScene::addFloatAttribute(const std::string& name)
{
    this->impl->addFloatAttribute(name);
}

void VDBPointsScene::setFloatAttribute(const std::string& name, const std::vector<float>& values)
{
    this->impl->setFloatAttributes(name, values);
}

std::vector<float> VDBPointsScene::getFloatAttribute(const std::string& name)
{
    return this->impl->getFloatAttributes(name);
}

bool VDBPointsScene::hasAttribute(const std::string& name)
{
    return this->impl->hasAttribute(name);
}

std::vector<std::string> VDBPointsScene::getAttributeNames() const
{
    const auto names = this->impl->getAttributeNames();
    std::vector<std::string> results;
    for (const auto& n : names) {
        results.push_back(n);
    }
    return results;
}

std::vector<std::string> VDBPointsScene::getFloatAttributeNames() const
{
    const auto names = this->impl->getAttributeNames();
    std::vector<std::string> results;
    for (const auto& n : names) {
        if (n == "P") {
            continue;
        }
        results.push_back(n);
    }
    return results;

}

