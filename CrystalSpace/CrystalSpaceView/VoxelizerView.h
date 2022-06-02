#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/DoubleView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class VoxelizerView : public IOkCancelView
{
public:
	VoxelizerView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	DoubleView divideLengthView;
};

	}
}