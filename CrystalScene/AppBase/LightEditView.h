#pragma once

#include "IEditCancelView.h"
#include "LightView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"
#include "../Scene/LightScene.h"
#include "../Scene/World.h"
#include "Canvas.h"

namespace Crystal {
	namespace UI {

class LightEditView : public IEditCancelView
{
public:
	LightEditView(const std::string& name, Scene::World* world, Canvas* canvas);

	void setValue(Scene::LightScene* value);

	void onEdit() override;

private:
	IntView idView;
	LightView lightView;
	StringView nameView;
};

	}
}
