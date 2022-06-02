#include "gtest/gtest.h"

#include "../Math/Gaussian2d.h"

using namespace Crystal::Math;

TEST(Gaussian2dTest, TestGetValue)
{
	Gaussian2d gaussian;
	const auto v0 = gaussian.getValue(0.0, 0.0);
	const auto v1 = gaussian.getValue(1.0, 1.0);
	EXPECT_GE(v0, v1);
}