#include "gtest/gtest.h"
#include "../Math/Matrix2d.h"
#include "../Math/Tolerance.h"

using namespace Crystal::Math;

namespace {
	const auto tolerance = 1.0e-12;
}

TEST(Matrix2dTest, TestRotationMatrix)
{
	const Matrix2dd expected
	(
		0.0, -1.0,
		1.0, 0.0
	);
	const auto actual = rotationMatrix(0.5 * PI);
	EXPECT_TRUE(areSame(expected, actual, tolerance));
}
