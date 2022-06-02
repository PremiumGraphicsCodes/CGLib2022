#include <gtest/gtest.h>

#include "../Math/Vector3d.h"
#include "../Math/Cylinder3d.h"

using namespace Crystal::Math;

namespace {
	constexpr auto tolerance = 1.0e-12;
}

TEST(Cylinder3dTest, TestGetPositionByUV)
{
	const Cylinder3d cylinder(1.0, 1.0, Vector3dd(0, 0, 0));

	{
		const auto actual = cylinder.getPosition(0, 0);
		const Vector3dd expected(1, 0, -0.5);
		EXPECT_TRUE(::areSame(expected, actual, tolerance));
	}

	{
		const auto actual = cylinder.getPosition(0, 1);
		const Vector3dd expected(1, 0, 0.5);
		EXPECT_TRUE(::areSame(expected, actual, tolerance));
	}
}

TEST(Cylinder3dTest, TestGetPositionByUVW)
{
	const Cylinder3d cylinder(1.0, 1.0, Vector3dd(0, 0, 0));

	{
		const auto actual = cylinder.getPosition(0.0, 0.0, 1.0);
		const Vector3dd expected(1, 0, -0.5);
		EXPECT_TRUE( ::areSame(expected, actual, tolerance) );
	}

	{
		const auto actual = cylinder.getPosition(0, 1.0, 1.0);
		const Vector3dd expected(1, 0, 0.5);
		EXPECT_TRUE( ::areSame(expected, actual, tolerance) );
	}
}