#pragma once

#include "IOkCancelView.h"
#include "Matrix3dView.h"
#include "ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class RotateView : public IOkCancelView
{
public:
	RotateView(const std::string& name, Scene::World* scene, Canvas* canvas);

	void onOk() override;

private:
	ObjectSelectView objectSelectView;
	Matrix3dView matrixView;
};

	}
}