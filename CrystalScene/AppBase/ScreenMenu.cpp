#include "ScreenMenu.h"
#include "imgui.h"
#include "../Scene/World.h"
#include "Canvas.h"

using namespace Crystal::UI;

void ScreenMenu::onShow()
{
	auto world = getWorld();
	auto canvas = getCanvas();

	//const auto& textures = model->getShaders()->getTextures()->getTextures();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("OnScreen")) {
			world->getRenderer()->setRenderTarget(Crystal::Scene::RenderTarget::Shaded);
		}
		if (ImGui::MenuItem("ParentId")) {
			world->getRenderer()->setRenderTarget(Crystal::Scene::RenderTarget::ParentId);
		}
		if (ImGui::MenuItem("ChildId")) {
			world->getRenderer()->setRenderTarget(Crystal::Scene::RenderTarget::ChildId);
		}
		ImGui::EndMenu();
	}
}
