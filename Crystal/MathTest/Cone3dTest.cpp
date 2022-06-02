#include "gtest/gtest.h"

#include "../Math/Cone3d.h"

using namespace Crystal::Math;

namespace {
	constexpr auto tolerance = 1.0e-12;
}

TEST(Cone3dTest, TestGetPositionUV)
{
	const Cone3d cone;
	{
		const auto& actual = cone.getPosition(0.0, 0.0);
		const Vector3dd expected(1.0, 0.0, 0.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
	{
		const auto& actual = cone.getPosition(0.5, 0.0);
		const Vector3dd expected(-1.0, 0.0, 0.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
	{
		const auto& actual = cone.getPosition(0.0, 0.5);
		const Vector3dd expected(0.5, 0.0, 0.5);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
	{
		const auto& actual = cone.getPosition(0.5, 0.5);
		const Vector3dd expected(-0.5, 0.0, 0.5);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
	{
		const auto& actual = cone.getPosition(1.0, 1.0);
		const Vector3dd expected(0.0, 0.0, 1.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
	{
		const auto& actual = cone.getPosition(0.0, 1.0);
		const Vector3dd expected(0.0, 0.0, 1.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
}

TEST(Cone3dTest, TestGetPositionUVW)
{
	const Cone3d cone;
	{
		const auto& actual = cone.getPosition(0.0, 0.0, 1.0);
		const Vector3dd expected(1.0, 0.0, 0.0);
		EXPECT_TRUE( areSame(expected, actual, tolerance) );
	}
	{
		const auto& actual = cone.getPosition(0.5, 0.0, 1.0);
		const Vector3dd expected(-1.0, 0.0, 0.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
	{
		const auto& actual = cone.getPosition(0.0, 0.5, 1.0);
		const Vector3dd expected(0.5, 0.0, 0.5);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
	{
		const auto& actual = cone.getPosition(0.5, 0.5, 1.0);
		const Vector3dd expected(-0.5, 0.0, 0.5);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
	{
		const auto& actual = cone.getPosition(1.0, 1.0, 1.0);
		const Vector3dd expected(0.0, 0.0, 1.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
}