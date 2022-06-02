#include "SelectionMenu.h"
#include "imgui.h"
#include "../Scene/World.h"
#include "Canvas.h"
#include "ControlPanel.h"

#include "ObjectSelectView.h"
#include "PositionSelectView.h"
#include "SphereRegionSelectView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

void SelectionMenu::onShow()
{
	auto model = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {

		if (ImGui::MenuItem("Object")) {
			control->setWindow(new ObjectSelectView("ObjectSelect", getWorld(), canvas));
		}
		if (ImGui::MenuItem("Position")) {
			control->setWindow(new PositionSelectView("PositionSelect", getWorld(), canvas));
		}
		/*
		if (ImGui::MenuItem("SphereRegion")) {
			control->setWindow(new SphereRegionSelectView("SphereRegionSelect", getModel(), canvas));
		}
		*/


		ImGui::EndMenu();
	}
}
