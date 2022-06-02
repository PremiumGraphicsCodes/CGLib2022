#pragma once

#include "IWFAddView.h"

#include "IntView.h"
#include "Torus3dView.h"

namespace Crystal {
	namespace UI {

class WFTorusView : public IWFAddView
{
public:
	WFTorusView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk();

private:
	IntView unumView;
	IntView vnumView;
	TorusView torusView;
};

	}
}