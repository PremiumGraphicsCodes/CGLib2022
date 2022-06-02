#include "gtest/gtest.h"

#include "../CrystalSpace/SparseVolumeBuilder.h"

#include "Crystal/Math/Box3d.h"
#include "Crystal/Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

TEST(SparseVolumeBuilderTest, TestAddBox)
{
	SparseVolumeBuilder builder;
	builder.build(Vector3df(1, 1, 1), 100);
	const Box3dd box(Vector3dd(20, 20, 20), Vector3dd(30, 40, 50));
	builder.add(box);
	auto volume = builder.get();
	EXPECT_TRUE( volume->exists({ 20,20,20 }));
	EXPECT_TRUE( volume->exists({ 30,40,50 }));
}

TEST(SparseVolumeBuilderTest, TestAddSphere)
{
	SparseVolumeBuilder builder;
	builder.build(Vector3df(1, 1, 1), 100);
	const Sphere3dd sphere(Vector3dd(0, 0, 0), 10);
	builder.add(sphere);
	auto volume = builder.get();
	EXPECT_FALSE(volume->exists({ -10,-10,-10 }));
	EXPECT_TRUE(volume->exists({ 0,0,0 }));
	EXPECT_FALSE(volume->exists({ 10,-10,10 }));
}