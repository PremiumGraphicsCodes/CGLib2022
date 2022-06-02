#include "pch.h"
#include "gtest/gtest.h"

#include "../../Crystal/Shape/Volume.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

namespace {
	const auto tolerance = 1.0e-12;
}

TEST(VolumeTest, TestGetCellLength)
{
	const std::array<size_t, 3> resolutions{ 2,1,4 };
	Volume<double> volume(Box3dd(Vector3dd(0,0,0), Vector3dd(2,2,2)), resolutions);
	const auto actual = volume.getCellLength();
	const auto expected = Vector3dd(1.0, 2.0, 0.5);
	EXPECT_TRUE(::areSame(expected, actual, ::tolerance));
}

TEST(VolumeTest, TestGetCellPosition)
{
	const std::array<size_t, 3> resolutions{ 2,1,4 };
	Volume<double> volume(Box3dd(Vector3dd(0, 0, 0), Vector3dd(2, 2, 2)), resolutions);
	
	{
		const auto actual = volume.getCellPosition(0, 0, 0);
		const auto expected = Vector3dd(0.5, 1.0, 0.25);
		EXPECT_TRUE(::areSame(expected, actual, ::tolerance));
	}
	{
		const auto actual = volume.getCellPosition(1, 0, 0);
		const auto expected = Vector3dd(1.5, 1.0, 0.25);
		EXPECT_TRUE(::areSame(expected, actual, ::tolerance));
	}
}

TEST(VolumeTest, TestIndexFromPosition)
{
	const std::array<size_t, 3> resolutions{ 2,1,4 };
	Volume<double> volume(Box3dd(Vector3dd(0, 0, 0), Vector3dd(2, 2, 2)), resolutions);

	{
		const auto p = Vector3dd(1.5, 1.0, 0.25);
		const auto actual = volume.getIndexFromPosition(p);
		EXPECT_EQ(1, actual[0]);
		EXPECT_EQ(0, actual[1]);
		EXPECT_EQ(0, actual[2]);
	}
}