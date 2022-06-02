#pragma once

#include "IWindow.h"
#include "../../Crystal/Graphics/ColorRGBA.h"

namespace Crystal {
	namespace UI {

class ColorRGBAView : public IWindow
{
public:
	ColorRGBAView(const std::string& name, const Graphics::ColorRGBAf& v);

	void onShow() override;

	Graphics::ColorRGBAf getValue() const;

	void setValue(const Graphics::ColorRGBAf& v);

private:
	float value[4];
};

	}
}