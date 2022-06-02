#pragma once

#include "IWindow.h"

#include "../Scene/World.h"
#include "Canvas.h"

namespace Crystal {
	namespace UI {

class IPopupButton : public IWindow
{
protected:
	IPopupButton(const std::string& name, Scene::World* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	~IPopupButton()
	{}


protected:
	virtual void onShow() = 0;

	virtual void onOk() = 0;

	virtual void onCancel() = 0;

	Scene::World* getModel() { return model; }

	Canvas* getCanvas() { return canvas; }

private:
	Scene::World* model;
	Canvas* canvas;
};
	}
}