#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/IntView.h"

namespace Crystal {
	namespace UI {

class RayTracerView : public IOkCancelView
{
public:
	RayTracerView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	IntView maxLevel;
};

	}
}