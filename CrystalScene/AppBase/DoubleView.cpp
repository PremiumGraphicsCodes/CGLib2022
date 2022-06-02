#include "DoubleView.h"

#include "imgui.h"

using namespace Crystal::UI;

DoubleView::DoubleView(const std::string& name) :
	DoubleView(name, 0.0)
{}

DoubleView::DoubleView(const std::string& name, const double value) :
	IWindow(name),
	value(value)
{}

void DoubleView::onShow()
{
	ImGui::InputDouble(name.c_str(), &value);
}
