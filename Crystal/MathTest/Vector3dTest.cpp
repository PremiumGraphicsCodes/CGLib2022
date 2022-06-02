#include "../Math/Vector3d.h"
#include "gtest/gtest.h"

using namespace Crystal::Math;

TEST(Vector3ddTest, TestIsEqualLoosely)
{
	const auto tolerance = 1.0e-12;
	EXPECT_TRUE( areSame(Vector3dd(0, 0, 0), Vector3dd(0, 0, 0), tolerance));
	EXPECT_FALSE(areSame(Vector3dd(1, 0, 0), Vector3dd(0, 0, 0), tolerance));
}

TEST(Vector3ddTest, TestGetDistanceSquared)
{
	const Vector3dd v1(0, 0, 0);
	const Vector3dd v2(1, 2, 4);
	EXPECT_DOUBLE_EQ(21, getDistanceSquared(v1, v2));
}

TEST(Vector3ddTest, TestGetDistance)
{
	const Vector3dd v1(0, 0, 0);
	const Vector3dd v2(1, 2, 4);
	EXPECT_DOUBLE_EQ(std::sqrt(21.0), getDistance(v1, v2));
}