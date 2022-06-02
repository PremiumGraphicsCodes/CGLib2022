#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/FloatView.h"
#include "CrystalScene/AppBase/ColorMapView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class SPHVolumeConverterView : public IOkCancelView
{
public:
	SPHVolumeConverterView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	FloatView particleRadiusView;
	FloatView thresholdView;
	FloatView cellLengthView;
	ColorMapView colorMapView;
};

	}
}