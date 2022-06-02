#include "ColorRGBAView.h"

#include "imgui.h"

using namespace Crystal::UI;
using namespace Crystal::Graphics;

ColorRGBAView::ColorRGBAView(const std::string& name, const ColorRGBAf& v) :
	IWindow(name)
{
	setValue(v);
}

void ColorRGBAView::onShow()
{
	ImGui::ColorEdit4(name.c_str(), value);
}

ColorRGBAf ColorRGBAView::getValue() const
{
	return Graphics::ColorRGBAf(value[0], value[1], value[2], value[3]);
}

void ColorRGBAView::setValue(const ColorRGBAf& v)
{
	value[0] = v.r;
	value[1] = v.g;
	value[2] = v.b;
	value[3] = v.a;
}

