#include "CameraMenu.h"
#include "Canvas.h"
#include "MenuItem.h"

#include "../Scene/World.h"
#include "../Command/Command.h"
#include "../Command/CommandFactory.h"
#include "../Command/CameraFitCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

CameraMenu::CameraMenu(const std::string& name, World* model, Canvas* canvas) :
	IMenu(name, model, canvas)
{
	add(new MenuItem("Fit", [&] { onFit(); }));
	add(new MenuItem("XY", [&] { onXY(); }));
	add(new MenuItem("YZ", [&] { onYZ(); }));
	add(new MenuItem("ZX", [&] { onZX(); }));
}

void CameraMenu::onFit()
{
	CameraFitCommand command;
	command.execute(getWorld());
}

void CameraMenu::onXY()
{
	CameraXYCommand command;
	command.execute(getWorld());
}

void CameraMenu::onYZ()
{
	CameraYZCommand command;
	command.execute(getWorld());
}

void CameraMenu::onZX()
{
	CameraZXCommand command;
	command.execute(getWorld());
}