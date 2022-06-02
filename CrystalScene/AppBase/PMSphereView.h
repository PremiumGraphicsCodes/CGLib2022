#pragma once

#include "IPMAddView.h"
#include "Sphere3dView.h"
#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class PMSphereView : public IPMAddView
{
public:
	PMSphereView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Sphere3dView sphereView;
	IntView unumView;
	IntView vnumView;
};

	}
}