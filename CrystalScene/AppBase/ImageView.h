#pragma once

#include "IWindow.h"
#include "StringView.h"
#include "../../Crystal/Graphics/Image.h"

namespace Crystal {
	namespace UI {

class ImageView : public IWindow
{
public:
	explicit ImageView(const std::string& name);

	ImageView(const std::string& name, const Graphics::Image& image);

	~ImageView();

	void onShow() override;

	void setValue(const Graphics::Image& image);

	Graphics::Image getValue() const { return image; }

private:
	Graphics::Image image;
	unsigned int textureId;
};

	}
}