#pragma once

#include "IPSAddView.h"

#include "Torus3dView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSTorusView : public IPSAddView
{
public:
	PSTorusView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	TorusView torusView;
	IntView countView;
};

	}
}