#include "gtest/gtest.h"

#include "../Math/Box3d.h"

using namespace Crystal::Math;

namespace {
	const double tolerance = 1.0e-12;
}

TEST(Box3dTest, TestGetMin)
{
	const Box3dd box1;
	const Box3dd box2(Vector3dd(1, 2, 3), Vector3dd(4, 5, 6));
	EXPECT_EQ(Vector3dd(0, 0, 0), box1.getMin());
	EXPECT_EQ(Vector3dd(1, 2, 3), box2.getMin());
}

TEST(Box3dTest, TestGetMax)
{
	EXPECT_EQ(Vector3dd(1, 1, 1), Box3dd().getMax());
	EXPECT_EQ(Vector3dd(4, 5, 6), Box3dd(Vector3dd(1, 2, 3), Vector3dd(4, 5, 6)).getMax());
}

TEST(Box3dTest, TestGetVolume)
{
	const Box3dd box1;
	const Box3dd box2(Vector3dd(0, 0, 0), Vector3dd(1, 2, 3));

	EXPECT_NEAR(1.0, box1.getVolume(), tolerance);
	EXPECT_NEAR(6.0, box2.getVolume(), tolerance);
}

TEST(Box3dTest, TestGetLength)
{
	Box3dd box(Vector3dd(1.0f, 1.0f, 1.0f), Vector3dd(1.0f, 2.0f, 3.0f));
	EXPECT_EQ(Vector3dd(0.0, 1.0, 2.0), box.getLength());
}

TEST(Box3dTest, TestHasIntersection)
{
	const Box3dd b1(Vector3dd(0, 0, 0), Vector3dd(1, 1, 1));
	const Box3dd b2(Vector3dd(2, 2, 2), Vector3dd(4, 4, 4));
	EXPECT_FALSE(b1.hasIntersection(b2));
}

TEST(Box3dTest, TestGetOverlapped)
{
	const Box3dd b1(Vector3dd(0, 0, 0), Vector3dd(2, 2, 2));
	const Box3dd b2(Vector3dd(1, 1, 1), Vector3dd(5, 5, 5));
	const Box3dd expected(Vector3dd(1, 1, 1), Vector3dd(2, 2, 2));
	const auto actual = b1.getOverlapped(b2);
	EXPECT_TRUE(expected.isSame(actual, tolerance));
}

TEST(Box3dTest, TestAdd)
{
	Box3dd b1(Vector3dd(0, 0, 0), Vector3dd(2, 2, 2));
	const Box3dd b2(Vector3dd(-1, 1, 1), Vector3dd(3, 3, 3));
	b1.add(b2);
	const Box3dd expected(Vector3dd(-1, 0, 0), Vector3dd(3, 3, 3));
	EXPECT_TRUE(expected.isSame(b1, tolerance));
}

TEST(Box3dTest, TestGetPosition)
{
	const Box3dd b1(Vector3dd(0, 0, 0), Vector3dd(2, 2, 2));
	EXPECT_EQ(Vector3dd(0,0,0), b1.getPosition(0, 0, 0));
	EXPECT_EQ(Vector3dd(2,0,0), b1.getPosition(1, 0, 0));
	EXPECT_EQ(Vector3dd(2,2,0), b1.getPosition(1, 1, 0));
	EXPECT_EQ(Vector3dd(0,2,0), b1.getPosition(0, 1, 0));
}

TEST(Box3dTest, TestIsInside)
{
	const Box3dd b1(Vector3dd(0, 0, 0), Vector3dd(2, 2, 2));
	EXPECT_TRUE( b1.isInside(Vector3dd(1, 1, 1)) );
	EXPECT_FALSE(b1.isInside(Vector3dd(5, 1, 1)) );
}

TEST(Box3dTest, TestContains)
{
	const Box3dd b1(Vector3dd(0, 0, 0), Vector3dd(2, 2, 2));
	EXPECT_TRUE( b1.contains(Vector3dd(0, 0, 0), tolerance));
	EXPECT_FALSE(b1.contains(Vector3dd(-1, 0, 0), tolerance));
}

TEST(Box3dTest, TestTranslate)
{
	Box3dd b1(Vector3dd(0, 0, 0), Vector3dd(2, 2, 2));
	b1.translate(Vector3dd(1, 2, 3));
	const Box3d expected(Vector3dd(1, 2, 3), Vector3dd(3, 4, 5));
	EXPECT_TRUE( b1.isSame(expected, 1.0e-12) );
}