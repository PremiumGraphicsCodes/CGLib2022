#include "gtest/gtest.h"

#include "../CrystalSpace/DistanceCalculator.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

TEST(DistanceCalculatorTest, TestGetDistanceTriangleAndPosition)
{
	const auto t = Triangle3d(Vector3dd(0, 0, 0), Vector3dd(10, 0, 0), Vector3dd(0, 10, 0));
	const auto p1 = Vector3dd(0, 0, 10);
	const auto p2 = Vector3dd(0, 0, -10);

	EXPECT_EQ(10.0, DistanceCalculator::getDistance(t, p1));
	EXPECT_EQ(-10.0, DistanceCalculator::getDistance(t, p2));

}