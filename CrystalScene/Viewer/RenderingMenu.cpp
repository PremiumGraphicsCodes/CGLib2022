#include "RenderingMenu.h"
#include "CrystalScene/AppBase/IMenuItem.h"
#include "CrystalScene/AppBase/ControlPanel.h"
#include "CrystalScene/AppBase/MenuItem.h"

#include "CubeMapShaderView.h"
#include "PolygonShaderView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;


RenderingMenu::RenderingMenu(const std::string& name, World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
	add(new MenuItem("CubeMap", [model, canvas, control] {
		control->setWindow(new CubeMapShaderView("CubeMap", model, canvas));
		}));

	add(new MenuItem("Polygon", [model, canvas, control] {
		control->setWindow(new PolygonShaderView("Polygon", model, canvas));
		}));
}
