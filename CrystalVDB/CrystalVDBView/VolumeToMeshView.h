#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/DoubleView.h"
#include "CrystalScene/AppBase/MaterialSelectView.h"

namespace Crystal {
	namespace UI {

class VolumeToMeshView : public IOkCancelView
{
public:
	VolumeToMeshView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	ObjectSelectView particleSystemSelectView;
	DoubleView radiusView;
};

	}
}