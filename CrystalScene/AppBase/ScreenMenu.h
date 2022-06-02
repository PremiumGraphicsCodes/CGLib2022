#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class ScreenMenu : public IMenu
{
public:
	ScreenMenu(const std::string& name, Scene::World* model, Canvas* canvas) :
		IMenu(name, model, canvas)
	{}

	virtual void onShow() override;
};

	}
}