#pragma once

#include "IVolAddView.h"
#include "Box3dView.h"

namespace Crystal {
	namespace UI {

class VolSphereView : public IVolAddView
{
public:
	VolSphereView(const std::string& name, Scene::World* world, Canvas* canvas);

	void onOk() override;

private:
	Box3dView boxView;
	IntView resolutionView;
};

	}
}