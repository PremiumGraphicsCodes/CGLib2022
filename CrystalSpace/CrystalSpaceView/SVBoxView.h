#pragma once

#include "ISVAddView.h"
#include "CrystalScene/AppBase/Box3dView.h"

namespace Crystal {
	namespace UI {

class SVBoxView : public ISVAddView
{
public:
	SVBoxView(const std::string& name, Scene::World* world, Canvas* canvas);

	void onOk() override;

private:
	Box3dView boxView;
	FloatView cellLengthView;
};

	}
}