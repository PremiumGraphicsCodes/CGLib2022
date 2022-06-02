#pragma once

#include <vector>
#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class Imagef
{
public:
	Imagef();

	Imagef(const int width, const int height);

	Imagef(const int width, const int height, const std::vector< float >& values);

	Imagef(const int width, const int height, const float v);

	static Imagef White(const int width, const int height);

	static Imagef Black(const int width, const int height);

	static Imagef Red(const int width, const int height);

	static Imagef Green(const int width, const int height);

	static Imagef Blue(const int width, const int height);

	bool isValid() const;

	void setColor(const int i, const int j, const ColorRGBAf& c) {
		const auto index = getIndex1d(i, j);
		values[index] = c.r;
		values[index + 1] = c.g;
		values[index + 2] = c.b;
		values[index + 3] = c.a;
	}

	ColorRGBAf getColor(const int x, const int y) const {
		const auto index = getIndex1d(x, y);
		const auto r = values[index];
		const auto g = values[index + 1];
		const auto b = values[index + 2];
		const auto a = values[index + 3];
		return ColorRGBAf(r, g, b, a);
	}


	std::vector<float> getValues() const { return values; }

	bool equals(const Imagef& rhs) const {
		return
			(getWidth() == rhs.getWidth()) &&
			(getHeight() == rhs.getHeight()) &&
			(values == rhs.values);
	}

	bool operator==(const Imagef& rhs) const { return equals(rhs); }

	bool operator!=(const Imagef& rhs) const { return !equals(rhs); }

	Imagef reversed()
	{
		Imagef dest(getWidth(), getHeight());
		for (int x = 0; x < getWidth(); ++x) {
			for (int y = 0; y < getHeight(); ++y) {
				const auto destY = getHeight() - y - 1;
				const auto c = getColor(x, y);
				dest.setColor(x, destY, c);
			}
		}
		return dest;
	}

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	int getIndex1d(const int x, const int y) const { return (y * width + x) * 4; }

private:
	int width;
	int height;
	std::vector< float > values;
};

	}
}
