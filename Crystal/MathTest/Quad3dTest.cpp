#include "gtest/gtest.h"

#include "../Math/Quad3d.h"

using namespace Crystal::Math;

namespace {
	const double tolerance = 1.0e-12;
}

TEST(Quad3dTest, TestGetPosition)
{
	const Quad3d quad(Vector3dd(0, 0, 0), Vector3dd(10, 0, 0), Vector3dd(0, 10, 0));
	EXPECT_TRUE( areSame( Vector3dd(5,0,0), quad.getPosition(0.5, 0.0), tolerance) );
	EXPECT_TRUE( areSame( Vector3dd(0,5,0), quad.getPosition(0.0, 0.5), tolerance));
}

TEST(Quad3dTest, TestGetNormal)
{
	const Quad3d quad(Vector3dd(0, 0, 0), Vector3dd(10, 0, 0), Vector3dd(0, 10, 0));
	EXPECT_TRUE(areSame(Vector3dd(0, 0, 1), quad.getNormal(0.5, 0.0), tolerance));
	EXPECT_TRUE(areSame(Vector3dd(0, 0, 1), quad.getNormal(0.0, 0.5), tolerance));
}


TEST(Quad3dTest, TestIsInside)
{
	const Quad3d quad(Vector3dd(0, 0, 0), Vector3dd(10, 0, 0), Vector3dd(0, 10, 0));
	EXPECT_TRUE( quad.isInside(Vector3dd(5, 5, 0)) );

	EXPECT_FALSE(quad.isInside(Vector3dd(11, 5, 0)));
	EXPECT_FALSE(quad.isInside(Vector3dd(-1, 5, 0)));
}