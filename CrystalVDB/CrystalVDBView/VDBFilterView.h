#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/IntView.h"

namespace Crystal {
	namespace UI {

class VDBFilterView : public IOkCancelView
{
public:
	VDBFilterView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	IntView widthView;
	IntView iterationView;
};

	}
}