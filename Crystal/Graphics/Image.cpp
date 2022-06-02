#include "Image.h"

using namespace Crystal::Graphics;

Image::Image() :
	width(0),
	height(0)
{}

Image::Image(const int width, const int height) :
	width(width),
	height(height),
	values(width* height * 4)
{}

Image::Image(const int width, const int height, const std::vector< unsigned char >& values) :
	width(width),
	height(height),
	values(values)
{
	assert(isValid());
}

Image::Image(const int width, const int height, const unsigned char v) :
	width(width),
	height(height)
{
	values.resize(width * height * 4);
	std::fill(values.begin(), values.end(), v);
	assert(isValid());
}

Image Image::White(const int width, const int height)
{
	std::vector<unsigned char> values(width * height * 4);
	for (int i = 0; i < width * height; ++i) {
		values[i * 4] = 255;
		values[i * 4 + 1] = 255;
		values[i * 4 + 2] = 255;
		values[i * 4 + 3] = 255;

	}
	return Image(width, height, values);
}

Image Image::Black(const int width, const int height)
{
	std::vector<unsigned char> values(width * height * 4);
	for (int i = 0; i < width * height; ++i) {
		values[i * 4] = 0;
		values[i * 4 + 1] = 0;
		values[i * 4 + 2] = 0;
		values[i * 4 + 3] = 255;
	}
	return Image(width, height, values);
}

Image Image::Red(const int width, const int height)
{
	std::vector<unsigned char> values(width * height * 4);
	for (int i = 0; i < width * height; ++i) {
		values[i * 4] = 255;
		values[i * 4 + 3] = 255;
	}
	return Image(width, height, values);
}

Image Image::Green(const int width, const int height)
{
	std::vector<unsigned char> values(width * height * 4);
	for (int i = 0; i < width * height; ++i) {
		values[i * 4 + 1] = 255;
		values[i * 4 + 3] = 255;
	}
	return Image(width, height, values);
}

Image Image::Blue(const int width, const int height)
{
	std::vector<unsigned char> values(width * height * 4);
	for (int i = 0; i < width * height; ++i) {
		values[i * 4 + 2] = 255;
		values[i * 4 + 3] = 255;
	}
	return Image(width, height, values);
}

bool Image::isValid() const
{
	return ((getWidth() * getHeight() * 4) == values.size());
}

void Image::setColor(const int i, const int j, const ColorRGBAuc& c)
{
	const auto index = getIndex1d(i, j);
	values[index] = c.r;
	values[index + 1] = c.g;
	values[index + 2] = c.b;
	values[index + 3] = c.a;
}

ColorRGBAuc Image::getColor(const int x, const int y) const
{
	const auto index = getIndex1d(x, y);
	const auto r = values[index];
	const auto g = values[index + 1];
	const auto b = values[index + 2];
	const auto a = values[index + 3];
	return ColorRGBAuc(r, g, b, a);
}

bool Image::equals(const Image& rhs) const
{
	return
		(getWidth() == rhs.getWidth()) &&
		(getHeight() == rhs.getHeight()) &&
		(values == rhs.values);
}

Image Image::reversed() const
{
	Image dest(getWidth(), getHeight());
	for (int x = 0; x < getWidth(); ++x) {
		for (int y = 0; y < getHeight(); ++y) {
			const auto destY = getHeight() - y - 1;
			const auto c = getColor(x, y);
			dest.setColor(x, destY, c);
		}
	}
	return dest;
}
