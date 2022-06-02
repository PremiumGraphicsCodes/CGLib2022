#pragma once

#include "IView.h"
#include "Vector3dView.h"
#include "Button.h"

namespace Crystal {
	namespace Scene {
		class World;
	}
	namespace UI {
		class Canvas;

class PositionSelectView : public IView
{
public:
	PositionSelectView(const std::string& name, Scene::World* model, Canvas* canvas);

	Math::Vector3dd getPosition() const { return positionView.getValue(); }

private:
	Vector3dView positionView;
	Button button;
	Scene::World* world;
	Canvas* canvas;
};

	}
}