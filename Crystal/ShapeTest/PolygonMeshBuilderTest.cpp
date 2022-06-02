#include "pch.h"

#include "../Shape/PolygonMeshBuilder.h"

#include "../Math/Quad3d.h"
#include "../Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

TEST(PolygonMeshBuilderTest, TestBuildByQuad)
{
    const Quad3d quad(Vector3dd(0, 0, 0), Vector3dd(10, 0, 0), Vector3dd(0, 10, 0));

    PolygonMeshBuilder builder;
    builder.add(quad, 1, 1);
    EXPECT_EQ(4, builder.getPositions().size());
    EXPECT_EQ(4, builder.getTexCoords().size());
    EXPECT_EQ(4, builder.getNormals().size());
    EXPECT_EQ(2, builder.getFaces().size());
}

TEST(PolygonMeshBuilderTest, TestBuildBySphere)
{
    const Sphere3dd sphere(Vector3dd(0, 0, 0), 10.0);

    PolygonMeshBuilder builder;
    builder.add(sphere, 2, 2);
    EXPECT_EQ(9, builder.getPositions().size());
    EXPECT_EQ(9, builder.getTexCoords().size());
    EXPECT_EQ(9, builder.getNormals().size());
    EXPECT_EQ(8, builder.getFaces().size());
}