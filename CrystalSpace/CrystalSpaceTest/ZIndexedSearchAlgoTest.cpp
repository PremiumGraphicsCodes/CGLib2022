#include "../CrystalSpace/ZIndexedSearchAlgo.h"

#include "gtest/gtest.h"

#include "../../Crystal/Shape/IParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

TEST(ZIndexedSearchAlgoTest, TestToIndex1d)
{
	ZIndexedSearchAlgo algo(1.0, Vector3dd(0,0,0));
	const auto i = algo.toIndex(Vector3dd(0.5, 1.5, 2.5));
	EXPECT_EQ(1, i[0]);
	EXPECT_EQ(2, i[1]);
	EXPECT_EQ(3, i[2]);
}

class TestPoint : public Crystal::Shape::IParticle
{
public:
	TestPoint(const Vector3dd& p) :
		position(p)
	{}

	Vector3dd getPosition() const { return position; }

private:
	Vector3dd position;
};

/*
TEST(ZIndexedSearchAlgoTest, TestSearchNeighbors)
{
	ZIndexedSearchAlgo algo(1.0, Vector3dd(0,0,0));
	TestPoint point1(Vector3dd(0, 0, 0));
	algo.add(&point1);
	algo.sort();
	const auto& neighbors = algo.findNeighbors(Vector3dd(0,0,0));
	EXPECT_EQ(1, neighbors.size());
}
*/
