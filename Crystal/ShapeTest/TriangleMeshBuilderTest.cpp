#include "pch.h"

#include "../Shape/TriangleMeshBuilder.h"

#include "../Math/Quad3d.h"
#include "../Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

TEST(TriangleMeshBuilderTest, TestBuildByQuad)
{
    const Quad3d quad(Vector3dd(0, 0, 0), Vector3dd(10, 0, 0), Vector3dd(0, 10, 0));

    TriangleMeshBuilder builder;
    builder.add(quad, 1, 1);
    auto mesh = builder.build();
    const auto faces = mesh->getFaces();
    EXPECT_EQ(2, faces.size());

    EXPECT_TRUE( areSame(Vector3dd(0, 0, 1), faces[0].normal, 1.0e-12) );
    EXPECT_TRUE( areSame(Vector3dd(0, 0, 1), faces[1].normal, 1.0e-12) );

    /*
    EXPECT_EQ(4, builder.getPositions().size());
    EXPECT_EQ(4, builder.getTexCoords().size());
    EXPECT_EQ(4, builder.getNormals().size());
    EXPECT_EQ(2, builder.getFaces().size());
    */
}

/*
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
*/