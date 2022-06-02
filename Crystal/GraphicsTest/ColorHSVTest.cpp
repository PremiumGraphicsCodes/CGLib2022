#include "gtest/gtest.h"

#include "../Graphics/ColorHSV.h"

using namespace Crystal::Graphics;

TEST(ColorHSVTest, TestToColorRGBAf)
{
	{
		const ColorHSV hsv(0.0, 0.0, 0.0);
		const auto rgb = hsv.toColorRGBf();
		EXPECT_TRUE(ColorRGBf(0.0, 0.0, 0.0) == rgb);
	}

	{
		const ColorHSV hsv(360.0, 1.0, 1.0);
		const auto rgb = hsv.toColorRGBf();
		EXPECT_TRUE(ColorRGBf(1.0, 0.0, 0.0) == rgb);
	}
}

TEST(ColorHSVTest, TestToColorRGBAuc)
{
	{
		const ColorHSV hsv(0.0, 0.0, 0.0);
		const auto rgb = hsv.toColorRGBuc();
		EXPECT_TRUE(ColorRGBuc(0, 0, 0) == rgb);
	}

	{
		const ColorHSV hsv(120.0, 1.0, 1.0);
		const auto rgb = hsv.toColorRGBuc();
		EXPECT_TRUE(ColorRGBuc(0, 255, 0) == rgb);
	}

	{
		const ColorHSV hsv(240.0, 1.0, 1.0);
		const auto rgb = hsv.toColorRGBuc();
		EXPECT_TRUE(ColorRGBuc(0, 0, 255) == rgb);
	}


	{
		const ColorHSV hsv(360.0, 1.0, 1.0);
		const auto rgb = hsv.toColorRGBuc();
		EXPECT_TRUE(ColorRGBuc(255, 0, 0) == rgb);
	}
}