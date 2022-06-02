#pragma once

#include "ITMAddView.h"
#include "Box3dView.h"

namespace Crystal {
	namespace UI {

class TMBoxView : public ITMAddView
{
public:
	TMBoxView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Box3dView boxView;
};

	}
}