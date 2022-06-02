#pragma once

#include "CrystalScene/AppBase/IMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"

namespace Crystal {
	namespace UI {

class SpaceMenu : public IMenu
{
public:
	SpaceMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control);
};

	}
}
