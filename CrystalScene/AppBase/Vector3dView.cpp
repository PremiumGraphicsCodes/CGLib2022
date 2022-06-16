#include "Vector3dView.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void Vector3dfView::onShow()
{
	ImGui::InputScalarN(name.c_str(), ImGuiDataType_Float, &value[0], 3);
}

void Vector3dView::onShow()
{
	ImGui::InputScalarN(name.c_str(), ImGuiDataType_Double, &value[0],3);
	//ImGui::InputFloat3(name.c_str(), &value[0]);
}
