#include "VDBPSMenu.h"

#include "CrystalScene/Scene/World.h"
#include "CrystalScene/AppBase/MenuItem.h"

#include "VDBPSBoxView.h"
#include "PSToVolumeView.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

VDBPSMenu::VDBPSMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas)
{
	add(new MenuItem("PSBox", [model, canvas, control]() {
		control->setWindow(new VDBPSBox("PSBox", model, canvas));
		}
	));

	add(new MenuItem("PSToMesh", [model, canvas, control]() {
		control->setWindow(new PSToVolumeView("PSToVolume", model, canvas));
		}
	));
}
