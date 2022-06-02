#include "gtest/gtest.h"

#include "Crystal/Shape/Particle.h"
#include "CrystalSpace/CrystalSpace/DynamicOctree.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

TEST(DynamicOctreeTest, TestDivide)
{
	Particle<float> p(Vector3dd(1,1,1), 1.0f);
	DynamicOctree octree(Box3dd(Vector3dd(0,0,0), Vector3dd(16, 16, 16)));
	octree.add(&p);
	octree.divide(1.0, { &p });
	octree.clear();
}

TEST(DynamicOctreeTest, TestCalculateBox)
{
	Particle<float> p1(Vector3dd(0.5, 0.5, 0.5), 1.0f);
	Particle<float> p2(Vector3dd(1, 3, 8), 1.0f);
	const auto box = DynamicOctree::calculateBox({ &p1, &p2 }, 1.0f);
	EXPECT_EQ(box.getMin(), Vector3dd(0, 0, 0));
	EXPECT_EQ(box.getMax(), Vector3dd(8, 8, 8));
}