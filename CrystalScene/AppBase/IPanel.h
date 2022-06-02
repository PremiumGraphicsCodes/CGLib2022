#pragma once

#include "IWindow.h"
#include "../Scene/World.h"
#include "Canvas.h"
#include <list>

namespace Crystal {
	namespace Scene {
		class World;
	}
	namespace UI {

class IPanel : public IWindow
{
public:
	IPanel(const std::string& name, Scene::World* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	virtual ~IPanel() {};

	virtual void onShow() override;

protected:
	Scene::World* getWorld() { return model; }

	Canvas* getCanvas() { return canvas; }

private:
	Scene::World* model;

	Canvas* canvas;
};

	}
}