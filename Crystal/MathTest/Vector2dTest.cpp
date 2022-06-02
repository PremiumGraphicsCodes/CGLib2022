#include "../Math/Vector2d.h"
#include "gtest/gtest.h"

using namespace Crystal::Math;

TEST(Vector2dTest, TestGetDistanceSquared)
{
	const Vector2dd v1(0, 0);
	const Vector2dd v2(2, 4);
	EXPECT_DOUBLE_EQ(20, getDistanceSquared(v1, v2));
}

TEST(Vector3dTest, TestGetDistance)
{
	const Vector2dd v1(0, 0);
	const Vector2dd v2(2, 4);
	EXPECT_DOUBLE_EQ(std::sqrt(20.0), getDistance(v1, v2));
}