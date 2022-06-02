#pragma once

#include "IPSAddView.h"

#include "Cone3dView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSConeView : public IPSAddView
{
public:
	PSConeView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Cone3dView coneView;
	IntView countView;
};

	}
}
