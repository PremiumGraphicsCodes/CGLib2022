#pragma once

#include "CrystalScene/AppBase/IMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"

namespace Crystal {
	namespace UI {

class PhysicsMenu : public IMenu
{
public:
	PhysicsMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control);

	//void onShow() override;

private:
	ControlPanel* control;
};

	}
}
