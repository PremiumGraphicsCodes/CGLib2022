#pragma once

#include <filesystem>
#include <vector>

namespace Crystal {
	namespace Renderer {

class HDRImage
{
public:
	bool load(const std::filesystem::path& path);

	std::vector<float> data;
	int width;
	int height;
};

	}
}