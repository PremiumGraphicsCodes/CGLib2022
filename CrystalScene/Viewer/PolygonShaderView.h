#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"

namespace Crystal {
	namespace UI {

class PolygonShaderView : public IOkCancelView
{
public:
	PolygonShaderView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void onOk() override;

private:
};

	}
}