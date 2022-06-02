#include "VDBPointsImpl.h"

using namespace Crystal::VDB;

void VDBPointsImpl::addFloatAttribute(const std::string& name)
{
    openvdb::points::appendAttribute<float>(grid->tree(), name);
}

std::vector<openvdb::Vec3f> VDBPointsImpl::getPositions() const
{
    std::vector<openvdb::Vec3f> positions;
    for (auto leafIter = grid->tree().cbeginLeaf(); leafIter; ++leafIter) {
        const auto& array = leafIter->constAttributeArray("P");
        openvdb::points::AttributeHandle<openvdb::Vec3f> positionHandle(array);
        for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
            openvdb::Vec3f voxelPosition = positionHandle.get(*indexIter);
            const auto xyz = indexIter.getCoord().asVec3d();
            openvdb::Vec3f worldPosition = grid->transform().indexToWorld(voxelPosition + xyz);
            auto index = *indexIter;
            //positions[index] = worldPosition;
            positions.push_back(worldPosition);
        }
    }
    return positions;
}

std::vector<float> VDBPointsImpl::getFloatAttributes(const std::string& name) const
{
    std::vector<float> values;
    for (auto leafIter = grid->tree().cbeginLeaf(); leafIter; ++leafIter) {
        //std::cout << "Leaf" << leafIter->origin() << std::endl;
        // Extract the position attribute from the leaf by name (P is position).
        const auto& array = leafIter->constAttributeArray(name);
        openvdb::points::AttributeHandle<float> floatHandle(array);
        for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
            const auto index = *indexIter;
            const auto v = floatHandle.get(*indexIter);
            values.push_back(v);
        }
    }
    /*
    for (int i = 0; i < values.size(); ++i) {
        if (values[i] == 0.0) {
            std::cout << i << std::endl;
        }
    }
    */

    return values;
}

void VDBPointsImpl::setFloatAttributes(const std::string& name, const std::vector<float>& values)
{
    int i = 0;
    for (auto leafIter = grid->tree().beginLeaf(); leafIter; ++leafIter) {
        //std::cout << "Leaf" << leafIter->origin() << std::endl;
        // Extract the position attribute from the leaf by name (P is position).
        //const auto array = leafIter->attributeArray(name);
        openvdb::points::AttributeWriteHandle<float> floatHandle(leafIter->attributeArray(name));
        for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
            const auto index = *indexIter;
            floatHandle.set(*indexIter, values[i++]);
        }
    }
}

/*
void VDBParticleSystemImpl::setValues(const std::vector<Particle>& particles)
{

}
*/

std::vector<std::string> VDBPointsImpl::getAttributeNames() const
{
    const auto desc = grid->tree().cbeginLeaf()->attributeSet().descriptor();
    const auto attrs = grid->tree().cbeginLeaf()->attributeSet();
    const auto map = desc.map();
    std::vector<std::string> names;
    for (auto m : map) {
        names.push_back(m.first);
    }
    /*
    for (int i = 0; i < desc.size(); ++i) {
        const auto type = attrs.get(i)->type();
    }
    */
    return names;
}

bool VDBPointsImpl::hasAttribute(const std::string& name) const
{
    const auto desc = grid->tree().cbeginLeaf()->attributeSet().descriptor();
    const auto map = desc.map();
    return map.find(name) != map.end();
}
