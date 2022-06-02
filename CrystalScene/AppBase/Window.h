#pragma once

#include <vector>
#include <memory>
#include "IMenu.h"
#include "IPanel.h"

struct GLFWwindow;

namespace Crystal {
	namespace UI {

class Window
{
public:
	Window(const std::string& title, Scene::World* model, Canvas* canvas);

	bool init();

	void show();

	void add(IMenu* menu) { this->menus.push_back( menu); }

	void add(IWindow* panel) { this->panels.push_back( panel); }

private:
	Scene::World* model;
	Canvas* canvas;
	std::vector< IMenu* > menus;
	std::vector< IWindow* > panels;
	GLFWwindow* window;
	std::string title;
};
	}
}