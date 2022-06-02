#include "gtest/gtest.h"

#include "../Math/Gaussian3d.h"

using namespace Crystal::Math;

TEST(Gaussian3dTest, TestGetValue)
{
	Gaussian3d gaussian;
	const auto v0 = gaussian.getValue(0.0, 0.0, 0.0);
	const auto v1 = gaussian.getValue(1.0, 1.0, 1.0);
	EXPECT_GE(v0, v1);
	//const auto expected = 
}