#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"

namespace Crystal {
	namespace UI {

class CubeMapView : public IOkCancelView
{
public:
	CubeMapView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void onOk() override;

private:
};

	}
}