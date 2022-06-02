#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/IView.h"

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;
		class MVPFluidEmitterScene;
	}
	namespace UI {

class MVPSamplerView : public IView
{
public:
	MVPSamplerView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onSplit();

	void onMerge();

private:
	//void split();

	//void merge();

	Scene::World* world;
	Canvas* canvas;
	Button splitButton;
	Button mergeButton;
};

	}
}