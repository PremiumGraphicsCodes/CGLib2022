#include "Matrix3dView.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Matrix3dView::Matrix3dView(const std::string& name) :
	Matrix3dView(name, Matrix3dd(1,0,0, 0,1,0, 0,0,1))
{
}

Matrix3dView::Matrix3dView(const std::string& name, const Matrix3dd& value) :
	IWindow(name)
{
	setValue(value);
}

void Matrix3dView::onShow()
{
	//ImGui::InputFloat3("Row1", value[0]);
	ImGui::InputScalarN("Row1", ImGuiDataType_Double, &value[0], 3);
	ImGui::InputScalarN("Row2", ImGuiDataType_Double, &value[1], 3);
	ImGui::InputScalarN("Row3", ImGuiDataType_Double, &value[2], 3);
}

void Matrix3dView::setValue(const Matrix3dd& value)
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			this->value[i][j] = value[i][j];
		}
	}
}

Matrix3dd Matrix3dView::getValue() const
{
	Matrix3dd m;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			m[i][j] = value[i][j];
		}
	}
	return m;
}