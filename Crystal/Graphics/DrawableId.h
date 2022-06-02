#pragma once

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class DrawableID
{
public:
	explicit DrawableID(const unsigned int id);

	explicit DrawableID(const ColorRGBAf& c);

	explicit DrawableID(const ColorRGBAuc& c);

	void fromColor(const ColorRGBAf& c);

	void fromColor(const ColorRGBAuc& c);

	ColorRGBAf toColor() const;

	bool equals(const DrawableID& rhs) const;

	bool operator==(const DrawableID& rhs) const { return equals(rhs); }

	bool operator!=(const DrawableID& rhs) const { return !equals(rhs); }

	bool operator<(const DrawableID& rhs) const { return childId < rhs.childId; }

	bool operator>(const DrawableID& rhs) const { return childId > rhs.childId; }

	unsigned int getId() const { return childId; }

private:
	unsigned int childId;
};

	}
}