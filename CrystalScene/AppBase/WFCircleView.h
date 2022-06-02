#pragma once

#include "IWFAddView.h"

#include "Circle3dView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class WFCircleView : public IWFAddView
{
public:
	WFCircleView(const std::string& name, Scene::World* world, Canvas* canvas);

	void onOk() override;

private:
	Circle3dView circleView;
	IntView unumView;
};
	}
}