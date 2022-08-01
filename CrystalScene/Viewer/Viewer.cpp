#include "../AppBase/Window.h"
#include "../AppBase/FileMenu.h"
#include "../AppBase/CameraMenu.h"
#include "../AppBase/MaskMenu.h"
#include "../AppBase/CtrlMenu.h"
#include "../AppBase/ScreenMenu.h"
#include "../AppBase/ShapeMenu.h"
#include "../AppBase/AppearanceMenu.h"
#include "../AppBase/SelectionMenu.h"
#include "../AppBase/SceneListPanel.h"
#include "../AppBase/ControlPanel.h"
#include "../AppBase/Canvas.h"

#include "../Scene/World.h"

#include "ColorMenu.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

int main(int, char**)
{
	World world;
	Canvas canvas;

	Window window("CrystalViewer", &world, &canvas);
	if (!window.init()) {
		assert(false);
		return 0;
	}

	auto control = new ControlPanel("Control", &world, &canvas);
	window.add(control);

	window.add(new FileMenu("File", &world, &canvas));
	window.add(new CameraMenu("Camera", &world, &canvas));
	window.add(new MaskMenu("Mask", &world, &canvas));
	window.add(new CtrlMenu("Ctrl", &world, &canvas));
	window.add(new ScreenMenu("Screen", &world, &canvas));
	window.add(new ShapeMenu("Shape", &world, &canvas, control));
	window.add(new AppearanceMenu("Appearance", &world, &canvas, control));
	window.add(new SelectionMenu("Selection", &world, &canvas, control));
	window.add(new ColorMenu("Color", &world, &canvas, control));

	window.add(new SceneListPanel("SceneList", &world, &canvas, control));

	window.show();

	return 0;
}
