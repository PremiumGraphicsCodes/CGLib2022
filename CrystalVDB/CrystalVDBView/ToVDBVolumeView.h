#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/Sphere3dView.h"
#include "CrystalScene/AppBase/IntView.h"

namespace Crystal {
	namespace UI {

class ToVDBVolumeView : public IOkCancelView
{
public:
	ToVDBVolumeView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Sphere3dView sphereView;
	IntView resolutionView;
	//ObjectSelectView particleSystemSelectView;
	//DoubleView radiusView;
};

	}
}