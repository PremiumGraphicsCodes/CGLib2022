#pragma once

#include <openvdb/openvdb.h>
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Math/Matrix3d.h"
#include "../../Crystal/Math/Matrix4d.h"

namespace Crystal {
    namespace VDB {

class Converter {
public:
    static openvdb::Vec3R toVDB(const Crystal::Math::Vector3dd& p);

    static std::vector<openvdb::Vec3s> toVDB(const std::vector<Crystal::Math::Vector3df>& positions);

    static std::vector<openvdb::Vec3R> toVDB(const std::vector<Crystal::Math::Vector3dd>& positions);

    //static openvdb::CoordBBox toVDB(const Math::Box3d& src);

    static Crystal::Math::Vector3df fromVDB(const openvdb::Vec3f& p);

    //static Crystal::Math::Vector3df fromVDB(const openvdb::Vec3s& p);

    static Crystal::Math::Vector3dd fromVDB(const openvdb::Vec3R& p);

    template<typename Dest>
    static std::vector<Dest> fromVDBf(const std::vector<openvdb::Vec3s>& positions);

    static std::vector<Crystal::Math::Vector3dd> fromVDB(const std::vector<openvdb::Vec3R>& positions);

    static openvdb::Vec3I toVDB(const std::array<unsigned int, 3>& indices);

    static std::array<unsigned int, 3> fromVDB(const openvdb::Vec3I& src);

    static openvdb::Vec4I toVDB(const std::array<unsigned int, 4>& indices);

    static std::array<unsigned int, 4> fromVDB(const openvdb::Vec4I& src);

    static openvdb::Mat3R toVDB(const Math::Matrix3dd& src);

    static openvdb::Mat4R toVDB(const Math::Matrix4dd& src);

};

    }
}