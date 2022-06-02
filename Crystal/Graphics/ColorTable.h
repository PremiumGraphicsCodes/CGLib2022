#pragma once

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class ColorTable
{
public:
	ColorTable() {}

	explicit ColorTable(const int resolution);

	int getResolution() const;

	void setColor(const int index, const Graphics::ColorRGBAf& color);

	Graphics::ColorRGBAf getColorFromIndex(const int i) const;

	std::vector< ColorRGBAf > getColors() const { return colors; }

	static ColorTable createDefaultTable(const int resolution);

private:
	std::vector<ColorRGBAf> colors;
};

	}
}