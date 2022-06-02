#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class AppearanceMenu : public IMenu
{
public:
	AppearanceMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
		IMenu(name, model, canvas),
		control(control)
	{}

	virtual void onShow() override;

private:
	ControlPanel* control;
};

	}
}