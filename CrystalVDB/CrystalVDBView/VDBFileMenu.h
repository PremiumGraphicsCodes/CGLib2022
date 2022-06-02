#pragma once

#include "CrystalScene/AppBase/IMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"

namespace Crystal {
	namespace UI {

class VDBFileMenu : public IMenu
{
public:
	VDBFileMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control);

private:
	void onImport();

	void onExport();
};

	}
}