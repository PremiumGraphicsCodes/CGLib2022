#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/Box3dView.h"

namespace Crystal {
	namespace UI {

class VolumeView : public IOkCancelView
{
public:
	VolumeView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onShow() override;

	void onOk() override;

private:
	Box3dView box;
};

	}
}