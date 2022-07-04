#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/FloatView.h"
#include "CrystalScene/AppBase/ColorMapView.h"

namespace Crystal {
	namespace UI {

class SPHDensityEstimatorView : public IOkCancelView
{
public:
	SPHDensityEstimatorView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	FloatView particleRadiusView;
	ColorMapView colorMapView;
};

	}
}