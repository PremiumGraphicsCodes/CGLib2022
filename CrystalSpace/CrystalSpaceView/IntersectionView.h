#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class IntersectionView : public IOkCancelView
{
public:
	IntersectionView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void onRayTriangle();

private:
	Button rayTriangleButton;
	DoubleView tolerance;
};

	}
}