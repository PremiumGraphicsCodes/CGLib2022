#pragma once

#include "IView.h"
#include "IntView.h"
#include "StringView.h"
#include "Canvas.h"

#include "../Scene/WireFrameScene.h"
#include "../Scene/World.h"

namespace Crystal {
	namespace UI {

class WireFrameEditView : public IWindow
{
public:
	WireFrameEditView(const std::string& name, Scene::World* world, Canvas* canvas);

	void onShow() override;

	void setValue(Scene::WireFrameScene* value);

private:
	//WireFrameView wire;
	IntView idView;
	StringView nameView;
};

	}
}
