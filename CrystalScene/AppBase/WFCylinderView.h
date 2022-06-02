#pragma once

#include "IWFAddView.h"
#include "IntView.h"
#include "Cylinder3dView.h"

namespace Crystal {
	namespace UI {

class WFCylinderView : public IWFAddView
{
public:
	WFCylinderView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	IntView unumView;
	IntView vnumView;
	Cylinder3dView cylinderView;
};

	}
}