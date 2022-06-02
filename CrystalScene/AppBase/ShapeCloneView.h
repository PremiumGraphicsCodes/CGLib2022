#pragma once

#include "IView.h"
#include "../Scene/World.h"
#include "Canvas.h"

#include "IOkCancelView.h"
#include "ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class ShapeCloneView : public IOkCancelView
{
public:
	ShapeCloneView(const std::string& name, Scene::World* model, Canvas* canvas);

	void onOk() override;

private:
	ObjectSelectView shapeSelectView;
};
	}
}