#include "ColorMenu.h"
#include "CrystalScene/AppBase/IMenuItem.h"
#include "CrystalScene/AppBase/ControlPanel.h"
#include "CrystalScene/AppBase/ColorMapView.h"
#include "CrystalScene/AppBase/MenuItem.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;


ColorMenu::ColorMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{	 
	add(new MenuItem(name, [model, canvas, control] {
		control->setWindow(new ColorMapView("ColorMap"));
	}));
}
