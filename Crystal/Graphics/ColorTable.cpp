#include "ColorTable.h"

#include "ColorHSV.h"

using namespace Crystal::Graphics;

ColorTable::ColorTable(const int resolution) :
	colors(resolution)
{
}

int ColorTable::getResolution() const
{
	return static_cast<int>(colors.size());
}

void ColorTable::setColor(const int index, const ColorRGBAf& color)
{
	colors[index] = color;
}

ColorRGBAf ColorTable::getColorFromIndex(const int i) const
{
	if (i >= colors.size()) {
		return colors.back();
	}
	return colors[i];
}

ColorTable ColorTable::createDefaultTable(const int resolution)
{
	ColorTable table(270);
	for (int i = 0; i < 270; ++i) {
		ColorHSV hsv(i * 1.0f, 1.0, 1.0);
		ColorRGBAf c(hsv.toColorRGBf(), 0.0f);
		table.setColor(269 - i, c);
	}
	return table;
}