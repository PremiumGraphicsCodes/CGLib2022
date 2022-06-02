#include "gtest/gtest.h"

#include "../CrystalSpace/CompactSpaceHash3d.h"

#include "../../Crystal/Shape/IParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

class TestPoint : public IParticle
{
public:
	TestPoint(const Vector3dd& position) :
		position(position)
	{}

	Vector3dd getPosition() const override { return position; }

private:
	Vector3dd position;
};

TEST(CompactSpaceHash3dTest, TestFindNeighbors)
{
	CompactSpaceHash3d spaceHash(1.0, 10);

	TestPoint point1(Vector3dd(1,1,1));
	TestPoint point2(Vector3dd(1,1,1));
	spaceHash.add(&point1);
	spaceHash.add(&point2);
	const auto neighbors = spaceHash.findNeighbors(&point1);
	EXPECT_EQ(1, neighbors.size());
}

TEST(CompactSpaceHash3dTest, TestToIndex)
{
	CompactSpaceHash3d spaceHash(1.0, 10);
	const auto ix = spaceHash.toIndex(Vector3df(0.5, 1.5, 2.5));
	EXPECT_EQ(ix[0], 0);
	EXPECT_EQ(ix[1], 1);
	EXPECT_EQ(ix[2], 2);
}

TEST(CompactSpaceHash3dTest, TestToPosition)
{
	CompactSpaceHash3d spaceHash(1.0, 10);
	const auto p1 = spaceHash.toPosition({ 0,1,2 });
	EXPECT_EQ(p1.x, 0.0);
	EXPECT_EQ(p1.y, 1.0);
	EXPECT_EQ(p1.z, 2.0);

	const auto p2 = spaceHash.toPosition({ -1,-2,-3 });
	EXPECT_EQ(p2.x, -1.0);
	EXPECT_EQ(p2.y, -2.0);
	EXPECT_EQ(p2.z, -3.0);
}

TEST(CompactSpaceHash3dTest, TestRemove)
{
	CompactSpaceHash3d spaceHash(1.0, 10);

	TestPoint point1(Vector3dd(1, 1, 1));
	TestPoint point2(Vector3dd(1, 1, 1));
	spaceHash.add(&point1);
	spaceHash.add(&point2);
	spaceHash.remove(&point2);
	const auto neighbors = spaceHash.findNeighbors(&point1);
	EXPECT_TRUE(neighbors.empty());
}