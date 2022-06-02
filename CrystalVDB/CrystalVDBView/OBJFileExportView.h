#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/FileSaveView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class OBJFileExportView : public IOkCancelView
{
public:
	OBJFileExportView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	ObjectSelectView vdbMeshSelectView;
	FileSaveView fileSaveView;
};

	}
}