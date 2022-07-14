#pragma once

#include "../../CrystalScene/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class RenderingMenu : public IMenu
{
public:
	RenderingMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control);

	//virtual void onShow() override;

private:
	ControlPanel* control;
};

	}
}