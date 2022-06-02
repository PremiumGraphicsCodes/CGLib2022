#include "WFAttributeView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

WFAttributeView::WFAttributeView(const std::string& name) :
	IWindow(name),
	width("Width", 1.0f),
	color("Color", glm::vec4(0, 0, 0, 0))
	//nameView("Name", "WireFrame")
{
}

void WFAttributeView::onShow()
{
	width.show();
	color.show();
	//nameView.show();
	//ImGui::ColorPicker4("Color", &color[0]);
}

WireFrameAttribute WFAttributeView::getValue() const
{
	Scene::WireFrameAttribute attr;
	attr.width = width.getValue();
	attr.color = color.getValue();
	return attr;
}
