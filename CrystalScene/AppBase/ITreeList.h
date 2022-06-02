#pragma once

#include "IWindow.h"

#include "../Scene/World.h"
#include "Canvas.h"

namespace Crystal {
	namespace UI {

class ITreeList : public IWindow
{
protected:
	ITreeList(const std::string& name, World* model, Canvas* canvas) :
		IWindow(name),
		repository(model),
		canvas(canvas)
	{}

	virtual ~ITreeList()
	{}

protected:
	virtual void onShow() = 0;

	std::string getName() const { return name; }

	World* getWorld() { return repository; }

	Canvas* getCanvas() { return canvas; }

private:
	World* repository;
	Canvas* canvas;
};

	}
}