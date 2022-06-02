#pragma once

#include "IPSAddView.h"
#include "Sphere3dView.h"
#include "DoubleView.h"

namespace Crystal {
	namespace UI {

class PSSphereView : public IPSAddView
{
public:
	PSSphereView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Sphere3dView sphereView;
	DoubleView divideLengthView;
};

	}
}