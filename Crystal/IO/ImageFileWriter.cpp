#include "ImageFileWriter.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../ThirdParty/stb/stb_image_write.h"

using namespace Crystal::Graphics;
using namespace Crystal::IO;

/*
bool ImageFileWriter::write(const std::experimental::filesystem::path& filePath, const Image& image)
{
	const auto& extension = filePath.extension();
	if (extension == ".bmp") {
		return write(filePath, image, ImageFileFormat::BMP);
	}
}
*/

bool ImageFileWriter::write(const std::filesystem::path& filePath, const Image& image, const ImageFileWriter::ImageFileFormat format)
{
	const auto& filename = filePath.filename().string();

	const int width = image.getWidth();
	const int height = image.getHeight();
	//int bpp = 0;

	std::vector<unsigned char> data;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			const auto& c = image.getColor(x,y);
			const auto r = c.r;
			const auto g = c.g;
			const auto b = c.b;
			const auto a = c.a;
			data.push_back(r);
			data.push_back(g);
			data.push_back(b);
			data.push_back(a);
		}
	}

	if (format == ImageFileFormat::BMP) {
		stbi_write_bmp(filename.c_str(), width, height, 0, data.data());
	}
	else if (format == ImageFileFormat::JPG) {
		stbi_write_jpg(filename.c_str(), width, height, 0, data.data(), 0);
	}
	else if (format == ImageFileFormat::PNG) {
		stbi_write_png(filename.c_str(), width, height, 0, data.data(), 0);
	}
	return true;
}
