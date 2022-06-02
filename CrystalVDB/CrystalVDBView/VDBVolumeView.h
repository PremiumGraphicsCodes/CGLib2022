#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class VDBVolumeView : public IOkCancelView
{
public:
	VDBVolumeView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	DoubleView scaleView;
};

	}
}