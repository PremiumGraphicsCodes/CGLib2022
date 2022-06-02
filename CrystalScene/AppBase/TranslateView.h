#pragma once

#include "IOkCancelView.h"
#include "Vector3dView.h"
#include "ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class TranslateView : public IOkCancelView
{
public:
	TranslateView(const std::string& name, Scene::World* scene, Canvas* canvas);

	void onOk() override;

private:
	ObjectSelectView objectSelectView;
	Vector3dView translateView;
};

	}
}