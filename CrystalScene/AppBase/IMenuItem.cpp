#include "IMenuItem.h"
#include "imgui.h"

using namespace Crystal::UI;

void IMenuItem::onShow()
{
	auto str = name.c_str();
	if (ImGui::MenuItem(str)) {
		onPushed();
	}
}
