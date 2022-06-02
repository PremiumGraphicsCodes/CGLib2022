#pragma once

#include "CrystalScene/AppBase/IMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"

namespace Crystal {
	namespace UI {

class VDBVolumeMenu : public IMenu
{
public:
	VDBVolumeMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control);
};

	}
}