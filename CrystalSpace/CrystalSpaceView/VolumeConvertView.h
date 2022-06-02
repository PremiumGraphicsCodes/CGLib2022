#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/DoubleView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class VolumeConvertView : public IOkCancelView
{
public:
	VolumeConvertView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	ObjectSelectView particleSystemSelectView;
	DoubleView searchRadiusView;
};

	}
}