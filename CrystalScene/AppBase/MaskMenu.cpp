#include "MaskMenu.h"
#include "imgui.h"
#include "../Scene/World.h"
#include "Canvas.h"

using namespace Crystal::UI;

void MaskMenu::onShow()
{
	auto model = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		auto renderer = model->getRenderer()->getObjectRenderer();
		auto mask = renderer->getMask();
		if (ImGui::MenuItem("Point")) {
			mask.showPoints = !mask.showPoints;
			renderer->setMask(mask);
//			model->updateViewModel();
		}
		if (ImGui::MenuItem("Line")) {
			mask.showLines = !mask.showLines;
			renderer->setMask(mask);
//			model->updateViewModel();
		}
		if (ImGui::MenuItem("Triangle")) {
			mask.showTrianlges = !mask.showTrianlges;
			renderer->setMask(mask);
//			model->updateViewModel();
		}

		ImGui::EndMenu();
	}
}
