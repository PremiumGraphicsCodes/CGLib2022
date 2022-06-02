#include <gtest/gtest.h>

#include "../Math/Circle2d.h"

using namespace Crystal::Math;

TEST(Circle2dTest, TestGetPosition)
{
	const Circle2d circle;

	{
		const auto& actual = circle.getPosition(0);
		const Vector2dd expected(1, 0);
		EXPECT_EQ(expected, actual);
	}

	{
		const auto& actual = circle.getPosition(0.5);
		const Vector2dd expected(-1, 0);
		EXPECT_TRUE(areSame(expected, actual, 1.0e-12));
	}

	{
		const auto& actual = circle.getPosition(1.0);
		const Vector2dd expected(1, 0);
		EXPECT_TRUE(areSame(expected, actual, 1.0e-12));
	}
}