#include "StringView.h"

#include "imgui.h"
#include "../../CrystalUI/CrystalUI/imgui_stdlib.h"

using namespace Crystal::UI;

void StringView::onShow()
{
	ImGui::InputText(name.c_str(), &value);
}
