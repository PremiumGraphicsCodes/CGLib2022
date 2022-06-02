#pragma once

#include "IWFAddView.h"
#include "IntView.h"
#include "WFAttributeView.h"

#include "Cone3dView.h"

namespace Crystal {
	namespace UI {

class WFConeView : public IWFAddView
{
public:
	WFConeView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	IntView unumView;
	IntView vnumView;
	Cone3dView coneView;
};

	}
}
