#include "imgui.h"

#include "IntView.h"

using namespace Crystal::UI;

void IntView::onShow()
{
	ImGui::InputInt(name.c_str(), &value);
}
