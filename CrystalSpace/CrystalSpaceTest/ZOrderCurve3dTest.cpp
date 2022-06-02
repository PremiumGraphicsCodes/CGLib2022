#include "gtest/gtest.h"

#include "../CrystalSpace/ZOrderCurve3d.h"

using namespace Crystal::Space;

TEST(ZOrderCurve3dTest, TestEncode)
{
	const ZOrderCurve3d curve;
	EXPECT_EQ(0, curve.encode({ 0,0,0 }));
	EXPECT_EQ(1, curve.encode({ 1,0,0 }));
	EXPECT_EQ(2, curve.encode({ 0,1,0 }));
	EXPECT_EQ(3, curve.encode({ 1,1,0 }));
	EXPECT_EQ(4, curve.encode({ 0,0,1 }));
	EXPECT_EQ(5, curve.encode({ 1,0,1 }));
	EXPECT_EQ(6, curve.encode({ 0,1,1 }));
	EXPECT_EQ(7, curve.encode({ 1,1,1 }));
	EXPECT_EQ(8, curve.encode({ 2,0,0 }));
	EXPECT_EQ(9, curve.encode({ 3,0,0 }));
}

TEST(ZOrderCurve3dTest, TestDecode)
{
	const ZOrderCurve3d curve;
	auto actual = curve.decode(0);
	EXPECT_EQ(0, actual[0]);
	EXPECT_EQ(0, actual[1]);
	EXPECT_EQ(0, actual[2]);

	actual = curve.decode(1);
	EXPECT_EQ(1, actual[0]);
	EXPECT_EQ(0, actual[1]);
	EXPECT_EQ(0, actual[2]);

	actual = curve.decode(2);
	EXPECT_EQ(0, actual[0]);
	EXPECT_EQ(1, actual[1]);
	EXPECT_EQ(0, actual[2]);

	actual = curve.decode(3);
	EXPECT_EQ(1, actual[0]);
	EXPECT_EQ(1, actual[1]);
	EXPECT_EQ(0, actual[2]);
}

TEST(ZOrderCurve3dTest, TestGetParent)
{
	const ZOrderCurve3d curve;
	EXPECT_EQ(2, curve.getParent(32, 47));

}