#include "IMenu.h"
#include "../../CrystalScene/AppBase/imgui.h"
#include "../../CrystalScene/AppBase/ControlPanel.h"
#include "../../CrystalScene/AppBase/ColorMapView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

void IMenu::onShow()
{
	auto model = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		for (auto c : children) {
			c->show();
		}
		ImGui::EndMenu();
	}
}