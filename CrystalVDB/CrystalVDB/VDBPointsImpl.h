#pragma once

#include "openvdb/openvdb.h"
#include "openvdb/points/PointConversion.h"

namespace Crystal {
    namespace VDB {

struct Particle
{
    openvdb::Vec3R position;
    openvdb::Real radius;
    openvdb::Real temperature;
};

class VDBPointsImpl
{
public:
    typedef openvdb::Vec3R  PosType;

    VDBPointsImpl()
    {}

    ~VDBPointsImpl()
    {}

    /// Return the total number of particles in list.
    ///  Always required!
    size_t size() const { return openvdb::points::pointCount(grid->tree()); }

    // The method below is only required for attribute transfer
    void getAtt(size_t n, openvdb::Index32& att) const { att = openvdb::Index32(n); }

    void addFloatAttribute(const std::string& name);

    std::vector<openvdb::Vec3f> getPositions() const;

    std::vector<float> getFloatAttributes(const std::string& name) const;

    void setFloatAttributes(const std::string& name, const std::vector<float>& values);

    //void setValues(const std::vector<Particle>& particles);

    std::vector<std::string> getAttributeNames() const;

    bool hasAttribute(const std::string& name) const;

    void setPtr(openvdb::points::PointDataGrid::Ptr grid) { this->grid = grid; }

    openvdb::points::PointDataGrid::Ptr getPtr() { return grid; }

private:
    openvdb::points::PointDataGrid::Ptr grid;
};
    }
}
