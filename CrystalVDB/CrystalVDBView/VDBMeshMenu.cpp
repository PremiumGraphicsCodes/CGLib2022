#include "VDBMeshMenu.h"

#include "VDBPMBoxView.h"
#include "MeshToVolumeView.h"
#include "OBJFileImportView.h"
#include "OBJFileExportView.h"

#include "VDBVolumeView.h"
#include "VolumeToMeshView.h"
#include "VolumeToPSView.h"

#include "CrystalScene/AppBase/MenuItem.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

VDBMeshMenu::VDBMeshMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas)
{
	add(new MenuItem("PMBox", [model, canvas, control]() {
		control->setWindow(new VDBPMBoxView("PMBox", model, canvas));
		}
	));
	add(new MenuItem("MeshToVolume", [model, canvas, control]() {
		control->setWindow(new MeshToVolumeView("MeshToVolume", model, canvas));
		}
	));
	add(new MenuItem("OBJImport", [model, canvas, control]() {
		control->setWindow(new OBJFileImportView("OBJImport", model, canvas));
	}
	));
	add(new MenuItem("OBJExport", [model, canvas, control]() {
		control->setWindow(new OBJFileExportView("OBJExport", model, canvas));
	}
	));
}