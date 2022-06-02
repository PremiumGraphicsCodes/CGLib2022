#include "Matrix2dView.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void Matrix2dView::onShow()
{
	ImGui::InputDouble("00", &value[0][0]);
	//ImGui::SameLine();
	ImGui::InputDouble("01", &value[0][1]);
	//ImGui::SameLine();

	//ImGui::SameLine();
	ImGui::InputDouble("10", &value[1][0]);
	//ImGui::SameLine();
	ImGui::InputDouble("11", &value[1][1]);
}
