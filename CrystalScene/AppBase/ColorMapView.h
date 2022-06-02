#pragma once

#include "IWindow.h"
#include "imgui.h"
#include "TextureView.h"
#include "FloatView.h"
#include "IntView.h"
#include "../../Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace UI {

class ColorMapView : public IView
{
public:
	ColorMapView(const std::string& name /*, const Graphics::ColorMap& value */);

	void onShow() override;

	Graphics::ColorMap getValue() const { return value; }

private:
	Graphics::ColorMap value;
	IntView resolution;
	FloatView minValue;
	FloatView maxValue;
};

	}
}