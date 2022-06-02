#include "gtest/gtest.h"

#include "../Math/Sphere3d.h"
#include "../Math/Box3d.h"

using namespace Crystal::Math;

namespace {
	const double tolerance = 1.0e-12;
}

TEST(Sphere3dTest, TestInnerOffset)
{
	Sphere3dd s(Vector3dd(0,0,0), 10.0);
	s.innerOffset(1.0f);
	EXPECT_EQ(9.0f, s.getRadius());
}

TEST(Sphere3dTest, TestOuterOffset)
{
	Sphere3dd s;
	s.outerOffset(1.0f);
	EXPECT_EQ(2.0f, s.getRadius());
}

TEST(Sphere3dTest, TestIsInside)
{
	const Sphere3dd s(Vector3dd(0.0, 0.0, 0.0), 1.0f);
	EXPECT_TRUE(s.isInside(Vector3dd(0.0f, 0.0f, 0.0f)));
	EXPECT_FALSE(s.isInside(Vector3dd(2.0f, 0.0f, 0.0f)));
}

TEST(Sphere3dTest, TestGetPosition)
{
	const Sphere3dd s(Vector3dd(0.0, 0.0, 0.0), 1.0);

	EXPECT_TRUE( areSame( Vector3dd( 0, 0, 1), s.getPosition( 0.0, 0.0,  1.0), tolerance) );
	EXPECT_TRUE( areSame( Vector3dd( 0, 0, 1), s.getPosition( 0.0, 0.5,  1.0), tolerance) );
	EXPECT_TRUE( areSame( Vector3dd( 0, 0, 1), s.getPosition( 0.0, 1.0,  1.0), tolerance) );

	EXPECT_TRUE( areSame( Vector3dd( 0, 0, 1), s.getPosition( 0.0, 0.5, 1.0 ), tolerance) );
	EXPECT_TRUE( areSame( Vector3dd(-1, 0, 0), s.getPosition( 0.5, 0.5, 1.0 ), tolerance) );
	EXPECT_TRUE( areSame( Vector3dd( 0, 0,-1), s.getPosition( 1.0, 0.5, 1.0 ), tolerance) );

	EXPECT_TRUE( areSame( Vector3dd( 0, 0,-1), s.getPosition( 1.0, 0.0, 1.0 ), tolerance) );
	EXPECT_TRUE( areSame( Vector3dd( 0, 0,-1), s.getPosition( 1.0, 0.5, 1.0 ), tolerance) );
	EXPECT_TRUE( areSame( Vector3dd( 0, 0,-1), s.getPosition( 1.0, 1.0, 1.0 ), tolerance) );
}

TEST(Sphere3dTest, TestGetNormal)
{
	const Sphere3dd s(Vector3dd(0.0, 0.0, 0.0), 1.0);

	EXPECT_TRUE(areSame(Vector3dd(0, 0, 1), s.getNormal(0.0, 0.0), tolerance));
	EXPECT_TRUE(areSame(Vector3dd(1, 0, 0), s.getNormal(0.5, 0.0), tolerance));
	EXPECT_TRUE(areSame(Vector3dd(0, 0,-1), s.getNormal(1.0, 0.0), tolerance));
}