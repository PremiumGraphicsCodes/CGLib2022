#pragma once

#include "../Graphics/Image.h"

#include <filesystem>

namespace Crystal {
	namespace IO {

class ImageFileWriter
{
public:
	enum class ImageFileFormat
	{
		BMP,
		PNG,
		JPG,
	};

	//bool write(const std::experimental::filesystem::path& filePath, const Graphics::Image& image);

	bool write(const std::filesystem::path& filePath, const Graphics::Image& image, const ImageFileFormat format);
private:
};

	}
}