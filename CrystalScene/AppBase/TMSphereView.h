#pragma once

#include "ITMAddView.h"
#include "Sphere3dView.h"
#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class TMSphereView : public ITMAddView
{
public:
	TMSphereView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Sphere3dView sphereView;
	IntView unumView;
	IntView vnumView;
};

	}
}