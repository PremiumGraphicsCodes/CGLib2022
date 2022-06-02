#pragma once

#include "IWFAddView.h"
#include "Box3dView.h"

namespace Crystal {
	namespace UI {

class WFBoxView : public IWFAddView
{
public:
	WFBoxView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Box3dView boxView;
};

	}
}

