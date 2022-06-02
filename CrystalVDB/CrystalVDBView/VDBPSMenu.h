#pragma once

#include "CrystalScene/AppBase/IMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"

namespace Crystal {
	namespace UI {

class VDBPSMenu : public IMenu
{
public:
	VDBPSMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control);
};

	}
}