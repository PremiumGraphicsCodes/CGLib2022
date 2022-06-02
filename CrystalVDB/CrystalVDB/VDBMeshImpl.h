#pragma once

#include "openvdb/openvdb.h"

namespace Crystal {
    namespace VDB {

class VDBMeshImpl
{
public:
    struct TriangleFace
    {
        openvdb::Vec3I indices;
        openvdb::Vec3s normal;
    };

    struct QuadFace
    {
        openvdb::Vec4I indices;
        openvdb::Vec3s normal;
    };

    std::vector<openvdb::Vec3s> points;
    std::vector<TriangleFace> triangles;
    std::vector<QuadFace> quads;

    std::vector<openvdb::Vec3I> getTriangles() const;

    std::vector<openvdb::Vec4I> getQuads() const;

    void clear()
    {
        points.clear();
        triangles.clear();
        quads.clear();
    }

    void updateNormals();
};

    }
}