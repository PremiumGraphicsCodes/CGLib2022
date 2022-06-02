#include "Float4View.h"

#include "imgui.h"

using namespace Crystal::UI;

Float4View::Float4View(const std::string& name) :
	IWindow(name)
{}

Float4View::Float4View(const std::string& name, const glm::vec4& value) :
	IWindow(name),
	value(value)
{}

void Float4View::onShow()
{
	ImGui::InputFloat4(name.c_str(), &value[0]);
}
