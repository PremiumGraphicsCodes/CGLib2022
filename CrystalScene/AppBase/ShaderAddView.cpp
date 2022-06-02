#include "ShaderAddView.h"
#include "ShaderView.h"

#include "imgui.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

ShaderAddView::ShaderAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	shader("Shader", model, canvas)
{
	//ImGui::InputTextMultiline()
}

void ShaderAddView::onShow()
{
	shader.show();
}

void ShaderAddView::onOk()
{

}