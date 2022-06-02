#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class MarchingCubesView : public IOkCancelView
{
public:
	MarchingCubesView(const std::string& name, Scene::World* model, Canvas* canvas);

	//void onShow() override;

	void onOk() override;

private:
	//std::array< DoubleView, 8 > values;
};

	}
}