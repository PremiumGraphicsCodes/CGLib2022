#include "Converter.h"

using namespace Crystal::VDB;

openvdb::Vec3R Converter::toVDB(const Crystal::Math::Vector3dd& p)
{
    return openvdb::Vec3R(p.x, p.y, p.z);
}

std::vector<openvdb::Vec3s> Converter::toVDB(const std::vector<Crystal::Math::Vector3df>& positions)
{
    std::vector<openvdb::Vec3s> dest(positions.size());
    for (int i = 0; i < positions.size(); ++i) {
        dest[i] = toVDB(positions[i]);
    }
    return dest;
}

std::vector<openvdb::Vec3R> Converter::toVDB(const std::vector<Crystal::Math::Vector3dd>& positions)
{
    std::vector<openvdb::Vec3R> dest(positions.size());
    for (int i = 0; i < positions.size(); ++i) {
        dest[i] = toVDB(positions[i]);
    }
    return dest;
}

/*
openvdb::CoordBBox Converter::toVDB(const Math::Box3d& src)
{
    const auto v1 = Converter::toVDB( src.getMin() );
    const auto v2 = Converter::toVDB( src.getMax() );
    openvdb::Coord c1(v1);
    return openvdb::CoordBBox(v1, v2);
}
*/

Crystal::Math::Vector3df Converter::fromVDB(const openvdb::Vec3f& p)
{
    return Crystal::Math::Vector3df(p[0], p[1], p[2]);
}

/*
Crystal::Math::Vector3df Converter::fromVDB(const openvdb::Vec3s& p)
{
    return Crystal::Math::Vector3df(p[0], p[1], p[2]);
}
*/

Crystal::Math::Vector3dd Converter::fromVDB(const openvdb::Vec3R& p)
{
    return Crystal::Math::Vector3dd(p[0], p[1], p[2]);
}

template<>
std::vector<Crystal::Math::Vector3df> Crystal::VDB::Converter::fromVDBf(const std::vector<openvdb::Vec3s>& positions)
{
    std::vector<Crystal::Math::Vector3df> dest(positions.size());
    for (int i = 0; i < positions.size(); ++i) {
        dest[i] = fromVDB( positions[i] );
    }
    return dest;
}

template<>
std::vector<Crystal::Math::Vector3dd> Crystal::VDB::Converter::fromVDBf(const std::vector<openvdb::Vec3s>& positions)
{
    std::vector<Crystal::Math::Vector3dd> dest(positions.size());
    for (int i = 0; i < positions.size(); ++i) {
        dest[i] = fromVDB(positions[i]);
    }
    return dest;
}

std::vector<Crystal::Math::Vector3dd> Converter::fromVDB(const std::vector<openvdb::Vec3R>& positions)
{
    std::vector<Crystal::Math::Vector3dd> dest(positions.size());
    for (int i = 0; i < positions.size(); ++i) {
        dest[i] = fromVDB(positions[i]);
    }
    return dest;
}

openvdb::Vec3I Converter::toVDB(const std::array<unsigned int, 3>& indices)
{
    return openvdb::Vec3I(indices[0], indices[1], indices[2]);
}

std::array<unsigned int, 3> Converter::fromVDB(const openvdb::Vec3I& src)
{
    return { src[0], src[1], src[2] };
}

openvdb::Vec4I Converter::toVDB(const std::array<unsigned int, 4>& indices)
{
    return openvdb::Vec4I(indices[0], indices[1], indices[2], indices[3]);
}

std::array<unsigned int, 4> Converter::fromVDB(const openvdb::Vec4I& src)
{
    return { src[0], src[1], src[2], src[3] };
}

openvdb::Mat3R Converter::toVDB(const Crystal::Math::Matrix3dd& src)
{
    return openvdb::Mat3R(
        src[0][0], src[0][1], src[0][2],
        src[1][0], src[1][1], src[1][2],
        src[2][0], src[2][1], src[2][2]
    );
}

openvdb::Mat4R Crystal::VDB::Converter::toVDB(const Math::Matrix4dd& src)
{
    return openvdb::Mat4R(
        src[0][0], src[0][1], src[0][2], src[0][3],
        src[1][0], src[1][1], src[1][2], src[1][3],
        src[2][0], src[2][1], src[2][2], src[2][3],
        src[3][0], src[3][1], src[3][2], src[3][3]
    );
}