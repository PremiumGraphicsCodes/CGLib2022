#pragma once

#include "IView.h"

#include "IntView.h"
#include "Button.h"

#include "../Scene/World.h"
#include "Canvas.h"

namespace Crystal {
	namespace UI {

class ObjectSelectView : public IView
{
public:
	ObjectSelectView(const std::string& name, Scene::World* model, Canvas* canvas);

	ObjectSelectView(const std::string& name, Scene::World* model, Canvas* canvas, const Scene::SceneType type);

	int getId() const { return idView.getValue(); }

private:
	IntView idView;
	Button pickButton;
	Scene::SceneType type;

private:
	void onPick(Scene::World* model, Canvas* canvas);
};

	}
}