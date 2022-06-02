#include "gtest/gtest.h"

#include "../CrystalSpace/ZOrderCurve2d.h"

using namespace Crystal::Space;

TEST(ZOrderCurve2dTest, TestEncode)
{
	const ZOrderCurve2d curve;
	EXPECT_EQ(0, curve.encode({ 0,0 }));
	EXPECT_EQ(1, curve.encode({ 1,0 }));
	EXPECT_EQ(2, curve.encode({ 0,1 }));
	EXPECT_EQ(3, curve.encode({ 1,1 }));
	EXPECT_EQ(4, curve.encode({ 2,0 }));
	EXPECT_EQ(5, curve.encode({ 3,0 }));
	EXPECT_EQ(6, curve.encode({ 2,1 }));
	EXPECT_EQ(7, curve.encode({ 3,1 }));
	EXPECT_EQ(8, curve.encode({ 0,2 }));
	EXPECT_EQ(9, curve.encode({ 1,2 }));
}

TEST(ZOrderCurve2dTest, TestDecode)
{
	const ZOrderCurve2d curve;
	auto actual = curve.decode(0);
	EXPECT_EQ(0, actual[0]);
	EXPECT_EQ(0, actual[1]);

	actual = curve.decode(1);
	EXPECT_EQ(1, actual[0]);
	EXPECT_EQ(0, actual[1]);

	actual = curve.decode(2);
	EXPECT_EQ(0, actual[0]);
	EXPECT_EQ(1, actual[1]);

	actual = curve.decode(3);
	EXPECT_EQ(1, actual[0]);
	EXPECT_EQ(1, actual[1]);
}
