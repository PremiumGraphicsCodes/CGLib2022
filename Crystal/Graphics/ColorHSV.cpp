#include "ColorHSV.h"

using namespace Crystal::Graphics;

ColorHSV::ColorHSV() :
	h(0.0),
	s(0.0),
	v(0.0)
{}

ColorHSV::ColorHSV(const float h, const float s, const float v) :
	h(h),
	s(s),
	v(v)
{}

ColorRGBf ColorHSV::toColorRGBf() const
{
	const auto max = v;
	const auto min = max - (s / 1.0f) * max;

	if (0 <= h && h <= 60) {
		const auto g = h / 60.0f * (max - min) + min;
		return ColorRGBf(max, g, min);
	}
	else if (h <= 120.0f) {
		const auto r = (120.0f - h) / 60.0f * (max - min) + min;
		return ColorRGBf(r, max, min);
	}
	else if (h <= 180.0f) {
		const auto b = (h - 120.0f) / 60.0f * (max - min) + min;
		return ColorRGBf(min, max, b);
	}
	else if (h <= 240.0f) {
		const auto g = (240.0f - h) / 60.0f * (max - min) + min;
		return ColorRGBf(min, g, max);
	}
	else if (h <= 300.0f) {
		const auto r = (h - 240.0f) / 60.0f * (max - min) + min;
		return ColorRGBf(r, min, max);
	}
	else if (h <= 360.0f) {
		const auto b = (360.0f - h) / 60.0f * (max - min) + min;
		return ColorRGBf(max, min, b);
	}
	else {
		assert(false);
		return ColorRGBf(0.0f, 0.0f, 0.0f);
	}
}

ColorRGBuc ColorHSV::toColorRGBuc() const
{
	const auto c = toColorRGBf();
	const auto r = c.r * 255;
	const auto g = c.g * 255;
	const auto b = c.b * 255;
	return ColorRGBuc(r, g, b);
}

