#include "gtest/gtest.h"
#include "../CrystalSpace/SparseVolume.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

namespace {
	constexpr auto tolerance = 1.0e-12;
}

TEST(SparseVolumeTest, TestGetPositionAt)
{
	const SparseVolumed sp(Vector3dd(2,2,2), 100);
	{
		const auto actual = sp.getPositionAt({ 0,0,0 });
		const Vector3dd expected(0, 0, 0);
		EXPECT_TRUE(::areSame(expected, actual, tolerance));
	}
	{
		const auto actual = sp.getPositionAt({ 1,2,3 });
		const Vector3dd expected(2, 4, 6);
		EXPECT_TRUE(::areSame(expected, actual, tolerance));
	}
	{
		const auto actual = sp.getPositionAt({ -1,-2,-3 });
		const Vector3dd expected(-2, -4, -6);
		EXPECT_TRUE(::areSame(expected, actual, tolerance));
	}
}

TEST(SparseVolumeTest, TestToIndex)
{
	const SparseVolumed sp(Vector3dd(1, 1, 1), 100);
	{
		const auto actual = sp.toIndex(Vector3df(0.9, 1.4, 1.9));
		EXPECT_EQ(actual[0], 1);
		EXPECT_EQ(actual[1], 1);
		EXPECT_EQ(actual[2], 2);
	}
	{
		const auto actual = sp.toIndex(Vector3df(-0.9, -1.4, -1.9));
		EXPECT_EQ(actual[0], -1);
		EXPECT_EQ(actual[1], -1);
		EXPECT_EQ(actual[2], -2);
	}
}