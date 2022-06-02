#include "CrystalScene/AppBase/Window.h"
#include "CrystalScene/AppBase/FileMenu.h"
#include "CrystalScene/AppBase/CameraMenu.h"
#include "CrystalScene/AppBase/CtrlMenu.h"
#include "CrystalScene/AppBase/ShapeMenu.h"
#include "CrystalScene/AppBase/AppearanceMenu.h"
#include "CrystalScene/AppBase/SceneListPanel.h"
#include "CrystalScene/AppBase/Canvas.h"
#include "CrystalScene/AppBase/ControlPanel.h"

#include "CrystalScene/Scene/World.h"

#include "VDBFileMenu.h"
#include "VDBPSMenu.h"
#include "VDBMeshMenu.h"
#include "VDBVolumeMenu.h"

#include "../CrystalVDB/VDBAdapter.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

int main(int, char**)
{
	World model;
	Canvas canvas;

	Window window("VDBView", &model, &canvas);
	if (!window.init()) {
		assert(false);
		return 0;
	}
	Crystal::VDB::VDBAdapter::init();
	auto control = new ControlPanel("Control", &model, &canvas);
	window.add(control);

	window.add(new FileMenu("File", &model, &canvas));
	window.add(new CameraMenu("Camera", &model, &canvas));
	window.add(new CtrlMenu("Ctrl", &model, &canvas));
	window.add(new ShapeMenu("Shape", &model, &canvas, control));
	window.add(new AppearanceMenu("Appearance", &model, &canvas, control));
	window.add(new VDBFileMenu("VDBFile", &model, &canvas, control));
	window.add(new VDBPSMenu("VDBPoints", &model, &canvas, control));
	window.add(new VDBMeshMenu("VDBMesh", &model, &canvas, control));
	window.add(new VDBVolumeMenu("VDBVolume", &model, &canvas, control));

	window.add(new SceneListPanel("Scene", &model, &canvas, control));


	window.show();

	return 0;
}

