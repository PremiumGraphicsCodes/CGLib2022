#include "ImageFileReader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Graphics;
using namespace Crystal::IO;

bool ImageFileReader::read(const std::string& filename)
{
	int width = 0;
	int height = 0;
	int bpp = 0;
	const auto& pixels = stbi_load(filename.c_str(), &width, &height, &bpp, 0);
	if (!(bpp == 3 || bpp == 4)) {
		return false;
	}
	int i = 0;
	image = Image(width, height);
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			const auto r = pixels[i];
			const auto g = pixels[i + 1];
			const auto b = pixels[i + 2];
			if (bpp == 3) {
				image.setColor(x, y, ColorRGBAuc(r, g, b, 255));
			}
			else if (bpp == 4) {
				const auto a = pixels[i + 3];
				image.setColor(x, y, ColorRGBAuc(r, g, b, a));
			}
			i += bpp;
		}
	}
	stbi_image_free(pixels);
	return true;
}
