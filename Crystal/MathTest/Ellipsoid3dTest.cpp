#include "gtest/gtest.h"

#include "../Math/Ellipsoid3d.h"
#include "../Math/Box3d.h"

using namespace Crystal::Math;

namespace {
	const double tolerance = 1.0e-12;
}

TEST(Ellipsoid3dTest, TestGetPosition)
{
	Ellipsoid3d e(Vector3dd(0,0,0), Vector3dd(1,0,0), Vector3dd(0,1,0), Vector3dd(0,0,2));
	const auto actual = e.getPosition(0, 0);
	const Vector3dd expected(0, 0, 2);
	EXPECT_TRUE(::areSame(expected, actual, tolerance));
}