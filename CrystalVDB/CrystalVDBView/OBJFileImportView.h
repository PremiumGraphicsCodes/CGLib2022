#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/FileOpenView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class OBJFileImportView : public IOkCancelView
{
public:
	OBJFileImportView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	FileOpenView fileOpenView;
};

	}
}