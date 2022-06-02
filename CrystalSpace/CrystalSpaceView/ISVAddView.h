#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/StringView.h"
#include "CrystalScene/AppBase/ComboBox.h"
#include "CrystalScene/AppBase/ColorMapView.h"
#include "../CrystalSpace/SparseVolume.h"

namespace Crystal {
	namespace UI {

class ISVAddView : public IOkCancelView
{
public:
	ISVAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addVolume(std::unique_ptr<Space::SparseVolumef> volume);

private:
	StringView nameView;
	ComboBox presenterView;
	ColorMapView colorMapView;
};

	}
}