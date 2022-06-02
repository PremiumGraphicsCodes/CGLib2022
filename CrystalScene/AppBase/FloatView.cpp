#include "FloatView.h"

#include "imgui.h"

using namespace Crystal::UI;

void FloatView::onShow()
{
	ImGui::InputFloat(name.c_str(), &value);
}
