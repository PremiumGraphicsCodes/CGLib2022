#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/Sphere3dView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class VDBPSBox : public IOkCancelView
{
public:
	VDBPSBox(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Sphere3dView sphereView;
	DoubleView divideLengthView;
};

	}
}