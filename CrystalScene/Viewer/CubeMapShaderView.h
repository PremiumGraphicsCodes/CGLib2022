#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"

namespace Crystal {
	namespace UI {

class CubeMapShaderView : public IOkCancelView
{
public:
	CubeMapShaderView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void onOk() override;

private:
};

	}
}