#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class CtrlMenu : public IMenu
{
public:
	CtrlMenu(const std::string& name, Scene::World* model, Canvas* canvas) :
		IMenu(name, model, canvas)
	{}

	virtual void onShow() override;
};

	}
}