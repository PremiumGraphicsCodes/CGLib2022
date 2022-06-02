#include <gtest/gtest.h>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Math/Plane3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../CrystalSpace/Overlap.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

namespace {
	const auto tolerance = 1.0e-12;
}

TEST(OverlapTest, TestBoxAndPlane)
{
	Overlap o;
	const Box3dd box(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	const Plane3d plane1(Vector3dd(5,5,5), Vector3dd(0, 0, 1));
	EXPECT_TRUE( o.overlap(box, plane1, tolerance) );
	const Plane3d plane2(Vector3dd(5, 5, 15), Vector3dd(0, 0, 1));
	EXPECT_FALSE( o.overlap(box, plane2, tolerance));

	//i.calculateIntersection(Box3dd(0,0,0), Box3dd(10,10,10),)
}

TEST(OverlapTest, TestBoxAndTriangle)
{
	Overlap o;
	const Box3dd box(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	const Triangle3d triangle({ Vector3dd(5,5,5), Vector3dd(6, 5, 5), Vector3dd(5, 6, 5) });
	EXPECT_TRUE( o.overlap(box, triangle) );

	const Box3dd box2(Vector3dd(10, 10, 10), Vector3dd(20, 20, 20));
	EXPECT_FALSE(o.overlap(box2, triangle));
}