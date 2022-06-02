#include "gtest/gtest.h"

#include "../Math/Circle3d.h"

using namespace Crystal::Math;

namespace {
	const double tolerance = 1.0e-12;
}

TEST(Circle3dTest, TestGetNormal)
{
	const Circle3d circle(Vector3dd(0, 0, 0), Vector3dd(1, 0, 0), Vector3dd(0, 1, 0));
	EXPECT_TRUE( areSame(Vector3dd(0,0,1), circle.getNormal(), tolerance) );
}

TEST(Circle3dTest, TestGetPosition)
{
	const Circle3d circle(Vector3dd(0, 0, 0), Vector3dd(1, 0, 0), Vector3dd(0, 1, 0));
	EXPECT_TRUE( areSame(Vector3dd(1,0,0), circle.getPosition(0.0), tolerance) );
	EXPECT_TRUE( areSame(Vector3dd(0,1,0), circle.getPosition(0.25), tolerance));
	EXPECT_TRUE( areSame(Vector3dd(-1,0,0), circle.getPosition(0.5), tolerance));
	EXPECT_TRUE(areSame(Vector3dd(0,-1, 0), circle.getPosition(0.75), tolerance));
	EXPECT_TRUE(areSame(Vector3dd(1, 0, 0), circle.getPosition(1.0), tolerance));

}