#include "gtest/gtest.h"
#include "../Math/Matrix3d.h"
#include "../Math/Tolerance.h"

using namespace Crystal::Math;

namespace {
	const auto tolerance = 1.0e-12;
}

TEST(Matrix3dTest, TestRotationMatrixX)
{
	const auto pi = PI;

	{
		const auto actual = rotationMatrixX(0.0);
		const auto expected = Matrix3dd
		(
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		);
		EXPECT_TRUE(AreSame(expected, actual, tolerance));
	}

	{
		const auto actual = rotationMatrixX(0.5 * pi);
		const auto expected = Matrix3dd
		(
			1.0, 0.0, 0.0,
			0.0, 0.0,-1.0,
			0.0, 1.0, 0.0
		);
		EXPECT_TRUE(AreSame( expected, actual, tolerance));
	}

	{
		const auto actual = rotationMatrixX(pi);
		const Matrix3dd expected
		(
			1.0, 0.0, 0.0,
			0.0,-1.0, 0.0,
			0.0, 0.0,-1.0
		);
		EXPECT_TRUE(AreSame(expected, actual, tolerance));
	}
}

TEST(Matrix3dTest, TestRotationMatrixY)
{
	const auto pi = PI;

	{
		const auto actual = rotationMatrixY(0.0);
		const auto expected = Matrix3dd
		(
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		);
		EXPECT_TRUE(AreSame(expected, actual, tolerance));
	}

	{
		const auto actual = rotationMatrixY(0.5 * pi);
		const auto expected = Matrix3dd
		(
			0.0, 0.0, 1.0,
			0.0, 1.0, 0.0,
		   -1.0, 0.0, 0.0
		);
		EXPECT_TRUE(AreSame(expected, actual, tolerance));
	}

	{
		const auto actual = rotationMatrixY(pi);
		const auto expected = Matrix3dd
		(
			-1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, -1.0
		);
		EXPECT_TRUE(AreSame(expected, actual, tolerance));
	}
}

TEST(Matrix3dTest, TestRotationMatrixZ)
{
	const auto pi = PI;

	{
		const auto actual = rotationMatrixZ(0.0);
		const auto expected = Matrix3dd
		(
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		);
		EXPECT_TRUE(AreSame(expected, actual, tolerance));
	}

	{
		const auto actual = rotationMatrixZ(0.5*pi);
		const auto expected = Matrix3dd
		(
			0.0,-1.0, 0.0,
			1.0, 0.0, 0.0,
			0.0, 0.0, 1.0
		);
		EXPECT_TRUE(AreSame(expected, actual, tolerance));
	}

	{
		const auto actual = rotationMatrixZ(pi);
		const auto expected = Matrix3dd
		(
			-1.0,0.0, 0.0,
			0.0,-1.0, 0.0,
			0.0, 0.0, 1.0
		);
		EXPECT_TRUE(AreSame(expected, actual, tolerance));
	}
}