#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace Scene {
		class IScene;
	}
	namespace UI {

class SceneListPanel : public IPanel
{
public:
	SceneListPanel(const std::string& name, Scene::World* model, Canvas* canvas, IPanel* control);

	void onShow() override;

private:
	void show(Scene::IScene* scene);

	//void show(Scene::IScene* )

	IPanel* control;
};

	}
}