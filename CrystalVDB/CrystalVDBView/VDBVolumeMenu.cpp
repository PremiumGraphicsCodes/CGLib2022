#include "VDBVolumeMenu.h"

#include "VDBVolumeView.h"
#include "VDBSphereView.h"
#include "VDBFilterView.h"
#include "VolumeToMeshView.h"
#include "VolumeToPSView.h"
#include "ToVDBVolumeView.h"

#include "CrystalScene/AppBase/MenuItem.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

VDBVolumeMenu::VDBVolumeMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas)
{
	add(new MenuItem("Box", [world, canvas, control]() {
		control->setWindow(new VDBVolumeView("Box", world, canvas));
		}
	));
	add(new MenuItem("Sphere", [world, canvas, control]() {
		control->setWindow(new VDBSphereView("Sphere", world, canvas));
		}
	));
	add(new MenuItem("Filter", [world, canvas, control]() {
		control->setWindow(new VDBFilterView("Filter", world, canvas));
		}
	));
	add(new MenuItem("VolumeToMesh", [world, canvas, control]() {
		control->setWindow(new VolumeToMeshView("VolumeToMesh", world, canvas));
		}
	));
	add(new MenuItem("VolumeToPS", [world, canvas, control]() {
		control->setWindow(new VolumeToPSView("VolumeToPS", world, canvas));
		}
	));
	add(new MenuItem("ToVDBVolume", [world, canvas, control]() {
		control->setWindow(new ToVDBVolumeView("ToVDBVolume", world, canvas));
		}
	));
}