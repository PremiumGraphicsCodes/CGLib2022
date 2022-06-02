#pragma once

#include "IWFAddView.h"
#include "IntView.h"
#include "Sphere3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFSphereView : public IWFAddView
{
public:
	WFSphereView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	IntView unumView;
	IntView vnumView;
	Sphere3dView sphereView;
};

	}
}