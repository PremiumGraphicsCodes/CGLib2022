#include "Double4View.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Double4View::Double4View(const std::string& name) :
	IWindow(name)
{
}

Double4View::Double4View(const std::string& name, const Vector4dd& value) :
	IWindow(name),
	value(value)
{
}

void Double4View::onShow()
{
	auto str = name.c_str();
	ImGui::InputScalarN(str, ImGuiDataType_Double, &value[0], 4);
}
