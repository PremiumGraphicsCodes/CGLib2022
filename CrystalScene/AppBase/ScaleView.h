#pragma once

#include "IOkCancelView.h"
#include "Vector3dView.h"
#include "ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class ScaleView : public IOkCancelView
{
public:
	ScaleView(const std::string& name, Scene::World* scene, Canvas* canvas);

	void onOk() override;

private:
	ObjectSelectView objectSelectView;
	Vector3dView scaleView;
};

	}
}