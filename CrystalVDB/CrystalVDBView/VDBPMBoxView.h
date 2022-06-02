#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/Sphere3dView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class VDBPMBoxView : public IOkCancelView
{
public:
	VDBPMBoxView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

};

	}
}