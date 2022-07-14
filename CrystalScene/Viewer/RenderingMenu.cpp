#include "RenderingMenu.h"
#include "CrystalScene/AppBase/IMenuItem.h"
#include "CrystalScene/AppBase/ControlPanel.h"
#include "CubeMapView.h"
#include "CrystalScene/AppBase/MenuItem.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;


RenderingMenu::RenderingMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
	add(new MenuItem(name, [model, canvas, control] {
		control->setWindow(new CubeMapView("CubeMap", model, canvas));
		}));
}
