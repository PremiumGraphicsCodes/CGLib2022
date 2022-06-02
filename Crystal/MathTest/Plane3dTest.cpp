#include "gtest/gtest.h"

#include "../Math/Plane3d.h"

using namespace Crystal::Math;

TEST(Plane3dTest, TestGetDistance)
{
	const Plane3d plane(Vector3dd(0, 0, 0), Vector3dd(0, 0, 1));
	EXPECT_DOUBLE_EQ(10.0, plane.getDistance(Vector3dd(0, 0, 10)));
}

TEST(Plane3dTest, TestCalculateD)
{
	const Plane3d plane(Vector3dd(0, 0, -1), Vector3dd(0, 0, 1));
	EXPECT_DOUBLE_EQ(-1.0, plane.calculateD());

	const Plane3d p(-1.0, Vector3dd(0, 0, 1));
	EXPECT_TRUE(areSame(Vector3dd(0, 0, -1), p.getOrigin(), 1.0e-12));
}