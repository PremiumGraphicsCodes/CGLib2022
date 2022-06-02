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

#include "PhysicsMenu.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

using namespace Crystal::Shader;

int main(int, char**)
{
	World world;
	Canvas canvas;

	Window window("FluidStudio", &world, &canvas);
	if (!window.init()) {
		assert(false);
		return 0;
	}

	auto control = new ControlPanel("Control", &world, &canvas);
	window.add(control);

	window.add(new FileMenu("File", &world, &canvas));
	window.add(new CameraMenu("Camera", &world, &canvas));
	window.add(new CtrlMenu("Ctrl", &world, &canvas));
	window.add(new ShapeMenu("Shape", &world, &canvas, control));
	window.add(new AppearanceMenu("Appearance", &world, &canvas, control));
	window.add(new PhysicsMenu("Physics", &world, &canvas, control));

	window.add(new SceneListPanel("Scene", &world, &canvas, control));

	window.show();

	return 0;
}

