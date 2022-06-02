#include "DrawableId.h"

using namespace Crystal::Graphics;

DrawableID::DrawableID(const unsigned int childId)
{
	this->childId = childId;
}

DrawableID::DrawableID(const ColorRGBAf& c)
{
	fromColor(c);
}

DrawableID::DrawableID(const ColorRGBAuc& c)
{
	fromColor(c);
}

void DrawableID::fromColor(const ColorRGBAf& c)
{
	ColorRGBAuc uc(c.r * 255, c.g * 255, c.b * 255, c.a * 255);
	fromColor(uc);
}

void DrawableID::fromColor(const ColorRGBAuc& c)
{
	childId = 0;
	childId |= c.a;
	childId <<= 8;
	childId |= c.b;
	childId <<= 8;
	childId |= c.g;
	childId <<= 8;
	childId |= c.r;
}

ColorRGBAf DrawableID::toColor() const
{
	const float red = (childId % 256) / 255.0f;
	const float green = ((childId / 256) % 256) / 255.0f;
	const float blue = ((childId / 256 / 256) % (256 * 256)) / 255.0f;
	const float alpha = ((childId / 256 / 256 / 256) % (256 * 256 * 256)) / 255.0f;
	return ColorRGBAf(red, green, blue, alpha);
}

bool DrawableID::equals(const DrawableID& rhs) const
{
	return this->childId == rhs.childId;
}
