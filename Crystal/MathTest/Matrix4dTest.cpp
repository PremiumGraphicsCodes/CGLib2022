#include "gtest/gtest.h"
#include "../Math/Matrix4d.h"

using namespace Crystal::Math;

TEST( Matrix4dTest, TestMultipy )
{
	const Matrix4dd lhs
	(
		1, 2, 3, 4,
		11, 12, 13, 14,
		21, 22, 23, 24,
		31, 32, 33, 34
	);
	const Matrix4dd rhs
	(
		100, 200, 300, 400,
		110, 120, 130, 140,
		210, 220, 230, 240,
		310, 320, 330, 340
	);
	const auto actual = lhs * rhs;
	const Matrix4dd expected
	(
		2190, 2380, 2570, 2760,
		9490, 10980, 12470, 13960,
		16790, 19580, 22370, 25160,
		24090, 28180, 32270, 36360
	);
	EXPECT_EQ(expected, actual);
}
