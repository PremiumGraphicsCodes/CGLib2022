#pragma once

#include "ColorRGB.h"
#include <cassert>

namespace Crystal {
	namespace Graphics {

class ColorHSV
{
public:
	ColorHSV();

	ColorHSV(const float h, const float s, const float v);

	float getH() const { return h; }

	float getS() const { return s; }

	float getV() const { return v; }

	void setH(const float h) { this->h = h; }

	void setS(const float s) { this->s = s; }

	void setV(const float v) { this->v = v; }

	//bool isSame(const ColorHSV& rhs, const double tolerance) const;

	ColorRGBf toColorRGBf() const;

	ColorRGBuc toColorRGBuc() const;

private:
	float h;
	float s;
	float v;
};
	}
}