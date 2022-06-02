#include "CheckBox.h"

#include "imgui.h"

using namespace Crystal::UI;

CheckBox::CheckBox(const std::string& name) :
	IWindow(name)
{}

CheckBox::CheckBox(const std::string& name, const bool v) :
	IWindow(name),
	value(v)
{}

void CheckBox::onShow()
{
	ImGui::Checkbox(name.c_str(), &value);
}
