#pragma once

#include "../../CrystalScene/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class ColorMenu : public IMenu
{
public:
	ColorMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control);

	//virtual void onShow() override;

private:
	ControlPanel* control;
};

	}
}