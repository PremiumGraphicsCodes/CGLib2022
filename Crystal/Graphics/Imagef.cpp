#include "Imagef.h"

using namespace Crystal::Graphics;

Imagef::Imagef() :
	width(0),
	height(0)
{}

Imagef::Imagef(const int width, const int height) :
	width(width),
	height(height),
	values(width* height * 4)
{}

Imagef::Imagef(const int width, const int height, const std::vector< float >& values) :
	width(width),
	height(height),
	values(values)
{
	assert(isValid());
}

Imagef::Imagef(const int width, const int height, const float v) :
	width(width),
	height(height)
{
	values.resize(width * height * 4);
	std::fill(values.begin(), values.end(), v);
	assert(isValid());
}

Imagef Imagef::White(const int width, const int height)
{
	std::vector<float> values(width * height * 4);
	for (int i = 0; i < width * height; ++i) {
		values[i * 4] = 1.0f;
		values[i * 4 + 1] = 1.0f;
		values[i * 4 + 2] = 1.0f;
		values[i * 4 + 3] = 1.0f;

	}
	return Imagef(width, height, values);
}

Imagef Imagef::Black(const int width, const int height)
{
	std::vector<float> values(width * height * 4);
	for (int i = 0; i < width * height; ++i) {
		values[i * 4] = 0;
		values[i * 4 + 1] = 0;
		values[i * 4 + 2] = 0;
		values[i * 4 + 3] = 1.0f;
	}
	return Imagef(width, height, values);
}

Imagef Imagef::Red(const int width, const int height)
{
	std::vector<float> values(width * height * 4);
	for (int i = 0; i < width * height; ++i) {
		values[i * 4] = 1.0f;
		values[i * 4 + 3] = 1.0f;
	}
	return Imagef(width, height, values);
}

Imagef Imagef::Green(const int width, const int height)
{
	std::vector<float> values(width * height * 4);
	for (int i = 0; i < width * height; ++i) {
		values[i * 4 + 1] = 1.0f;
		values[i * 4 + 3] = 1.0f;
	}
	return Imagef(width, height, values);
}

Imagef Imagef::Blue(const int width, const int height)
{
	std::vector<float> values(width * height * 4);
	for (int i = 0; i < width * height; ++i) {
		values[i * 4 + 2] = 1.0f;
		values[i * 4 + 3] = 1.0f;
	}
	return Imagef(width, height, values);
}

bool Imagef::isValid() const
{
	return ((getWidth() * getHeight() * 4) == values.size());
}
