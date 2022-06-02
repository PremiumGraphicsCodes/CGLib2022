#include "gtest\gtest.h"
#include "../Math/Ray3d.h"

using namespace Crystal::Math;

namespace {
	double tolerance = 1.0e-12;
}

TEST(Ray3dTest, TestGetPosition)
{
	const Ray3d ray(Vector3dd(0, 0, 0), Vector3dd(1, 0, 0));
	const auto& actual = ray.getPosition(5.0);
	const Vector3dd expected(5.0, 0.0, 0.0);
	EXPECT_TRUE(areSame(expected, actual, tolerance));
}