#include "AppearanceMenu.h"
#include "imgui.h"
#include "../Scene/World.h"
#include "Canvas.h"
#include "ControlPanel.h"

#include "LightAddView.h"
#include "MaterialAddView.h"
#include "TextureAddView.h"
#include "ShaderAddView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

void AppearanceMenu::onShow()
{
	auto model = getWorld();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {

		if (ImGui::MenuItem("Light")) {
			control->setWindow(new LightAddView("Light", getWorld(), canvas));
		}
		if (ImGui::MenuItem("Material")) {
			control->setWindow(new MaterialAddView("Material", getWorld(), canvas));
		}
		if (ImGui::MenuItem("Texture")) {
			control->setWindow(new TextureAddView("Texture", getWorld(), canvas));
		}
		if (ImGui::MenuItem("Shader")) {
			control->setWindow(new ShaderAddView("Shader", getWorld(), canvas));
		}

		ImGui::EndMenu();
	}
}
