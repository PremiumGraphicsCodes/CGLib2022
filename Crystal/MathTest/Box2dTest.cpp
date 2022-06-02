#include "gtest/gtest.h"
#include "../Math/Box2d.h"

using namespace Crystal::Math;

namespace {
	double tolerance = 1.0e-12;
}

TEST(Box2dTest, TestGetArea)
{
	const Box2d box(Vector2dd(0, 0), Vector2dd(1, 1));
	EXPECT_DOUBLE_EQ(1.0, box.getArea());
}

TEST(Box2dTest, TestAdd)
{
	Box2d box(Vector2dd(0, 0), Vector2dd(1, 1));
	box.add(Vector2dd(10, 0));
	Box2d expected(Vector2dd(0, 0), Vector2dd(10, 1));
	EXPECT_TRUE(expected.isSame(box, tolerance));
}