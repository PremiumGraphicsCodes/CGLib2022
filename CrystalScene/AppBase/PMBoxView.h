#pragma once
#include "IPMAddView.h"

#include "Box3dView.h"

namespace Crystal {
	namespace UI {

class PMBoxView : public IPMAddView
{
public:
	PMBoxView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Box3dView boxView;
};

	}
}