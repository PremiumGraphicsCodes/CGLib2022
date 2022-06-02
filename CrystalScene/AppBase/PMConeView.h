#pragma once

#include "IPMAddView.h"

#include "Cone3dView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class PMConeView : public IPMAddView
{
public:
	PMConeView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Cone3dView coneView;
};

	}
}