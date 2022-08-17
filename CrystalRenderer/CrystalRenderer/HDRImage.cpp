#include "HDRImage.h"

#include "../../Crystal/ThirdParty/stb/stb_image.h"

using namespace Crystal::Renderer;

bool HDRImage::load(const std::filesystem::path& path)
{
	stbi_set_flip_vertically_on_load(true);
	int nrComponents;
	float* d = stbi_loadf(path.string().c_str(), &width, &height, &nrComponents, 0);
	if (d == nullptr) {
		return false;
	}
	const auto size = width * height * nrComponents;
	this->data.resize(size);
	for (int i = 0; i < size; ++i) {
		this->data[i] = d[i];
	}
	stbi_image_free(d);
	return true;
}
