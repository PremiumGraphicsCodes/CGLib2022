#pragma once

#include "ISVAddView.h"
#include "CrystalScene/AppBase/Sphere3dView.h"

namespace Crystal {
	namespace UI {

class SVSphereView : public ISVAddView
{
public:
	SVSphereView(const std::string& name, Scene::World* world, Canvas* canvas);

	void onOk() override;

private:
	Sphere3dView sphereView;
	FloatView cellLengthView;
};

	}
}