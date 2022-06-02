#include "gtest\gtest.h"

#include "../Math/Triangle3d.h"
#include "../Math/Tolerance.h"

using namespace Crystal::Math;

TEST(Triangle3dTest, TestGetNormal)
{
	const Triangle3d triangle
	(
		Vector3dd(0, 0, 0),
		Vector3dd(1, 0, 0),
		Vector3dd(0, 1, 0)
	);
	EXPECT_EQ(Vector3dd(0, 0, 1), triangle.getNormal());
}

TEST(Triangle3dTest, TestGetArea)
{
	const Triangle3d triangle
	(
		Vector3dd(0,0,0),
		Vector3dd(1,0,0),
		Vector3dd(0,1,0)
	);
	EXPECT_DOUBLE_EQ(0.5, triangle.getArea());
}

TEST(Triangle3dTest, TestTranslate)
{
	Triangle3d triangle
	(
		Vector3dd(0,0,0),
		Vector3dd(1,0,0),
		Vector3dd(0,1,0)
	);
	triangle.translate(Vector3dd(1, 2, 3));

	const Triangle3d expected
	(
		Vector3dd(1,2,3),
		Vector3dd(2,2,3),
		Vector3dd(1,3,3)
	);
	EXPECT_TRUE(expected.isSame(triangle, 1.0e-12));
}

TEST(Triangle3dTest, TestTransform)
{
	Triangle3d triangle
	(
		Vector3dd(0,0,0),
		Vector3dd(1,0,0),
		Vector3dd(0,1,0)
	);

	const Triangle3d expected
	(
		Vector3dd( 0, 0, 0),
		Vector3dd(-1, 0, 0),
		Vector3dd( 0,-1, 0)
	);

	const auto& matrix = rotationMatrixZ(PI);
	triangle.transform(matrix);

	EXPECT_TRUE(expected.isSame(triangle, 1.0e-12));
}
