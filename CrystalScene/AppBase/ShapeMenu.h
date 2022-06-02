#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class ShapeMenu : public IMenu
{
public:
	ShapeMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);
};

	}
}