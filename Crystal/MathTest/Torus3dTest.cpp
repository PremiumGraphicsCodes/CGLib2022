#include "gtest/gtest.h"

#include "../Math/Torus3d.h"

using namespace Crystal::Math;

namespace {
	double tolerance = 1.0e-12;
}

TEST(Torus3dTest, TestGetPosition)
{
	Torus3d torus;
	{
		const auto& actual = torus.getPosition(0.0, 0.0);
		const Vector3dd expected(1.5, 0.0, 0.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
	{
		const auto& actual = torus.getPosition(0.0, 0.5);
		const Vector3dd expected(0.5, 0.0, 0.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
	{
		const auto& actual = torus.getPosition(0.5, 0.0);
		const Vector3dd expected(-1.5, 0.0, 0.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
	{
		const auto& actual = torus.getPosition(0.5, 0.5);
		const Vector3dd expected(-0.5, 0.0, 0.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
}