#include "gtest/gtest.h"

#include "../Math/Line3d.h"
#include "../Math/Ray3d.h"
#include "../Math/Tolerance.h"

using namespace Crystal::Math;

namespace {
	double tolerance = 1.0e-12;
}

TEST(Line3dTest, TestGetPosition)
{
	const Line3dd line(Vector3dd(0, 0, 0), Vector3dd(10, 0, 0));
	{
		const auto& actual = line.getPosition(0.0);
		const Vector3dd expected(0.0, 0.0, 0.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}

	{
		const auto& actual = line.getPosition(0.5);
		const Vector3dd expected(5.0, 0.0, 0.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}

	{
		const auto& actual = line.getPosition(1.0);
		const Vector3dd expected(10.0, 0.0, 0.0);
		EXPECT_TRUE(areSame(expected, actual, tolerance));
	}
}

TEST(Line3dTest, TestTransform)
{
	const auto& matrix = rotationMatrixZ(0.5 * PI);

	Line3dd line(Vector3dd(10, 0, 0), Vector3dd(10, 0, 0));
	line.transform(matrix);
	Line3dd expected(Vector3dd(0, -10, 0), Vector3dd(0, -10, 0));
	EXPECT_TRUE( expected.isSame(line, tolerance ) );

}

TEST(Line3dTest, TestToRay)
{
	const Line3dd line(Vector3dd(0, 0, 0), Vector3dd(10, 0, 0));
	const Ray3d expected(Vector3dd(0, 0, 0), Vector3dd(1, 0, 0));
	const auto& actual = line.toRay();
	EXPECT_TRUE(expected.isSame(actual, tolerance));
}