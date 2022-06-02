#pragma once

#include "IOkCancelView.h"
#include "ObjectSelectView.h"
#include "Matrix4dView.h"

namespace Crystal {
	namespace UI {

class TransformView : public IOkCancelView
{
public:
	TransformView(const std::string& name, Scene::World* model, Canvas* canvas);

	void onOk() override;

private:
	ObjectSelectView objectSelectView;
	Matrix4dView matrixView;
};

	}
}