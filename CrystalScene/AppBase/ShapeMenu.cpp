#include "ShapeMenu.h"
#include "Canvas.h"
#include "ControlPanel.h"

#include "PSBoxView.h"
#include "PSConeView.h"
#include "PSCylinderView.h"
#include "PSSphereView.h"
#include "PSTorusView.h"

#include "WFBoxView.h"
#include "WFCircleView.h"
#include "WFConeView.h"
#include "WFCylinderView.h"
#include "WFSphereView.h"
#include "WFEllipsoidView.h"
#include "WFTorusView.h"

#include "PMBoxView.h"
#include "PMQuadView.h"
#include "PMSphereView.h"
#include "PMConeView.h"

#include "TMBoxView.h"
#include "TMSphereView.h"

#include "VolSphereView.h"
#include "VoxelSphereView.h"

#include "SolidBoxView.h"

#include "ScaleView.h"
#include "TranslateView.h"
#include "TransformView.h"
#include "RotateView.h"

#include "DeleteView.h"
#include "MenuItem.h"

#include "../Scene/World.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

namespace {

	class PSGenerationMenu : public IMenu
	{
	public:
		PSGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
			IMenu(name, world, canvas)
		{
			add(new MenuItem("PSSphere", [world, canvas, control] {
				control->setWindow(new PSSphereView("PSSphere", world, canvas));
				}));

			add(new MenuItem("PSBox", [world, canvas, control] {
				control->setWindow(new PSBoxView("PSBox", world, canvas));
				}));

			add(new MenuItem("PSCone", [world, canvas, control] {
				control->setWindow(new PSConeView("PSCone", world, canvas));
				}));

			add(new MenuItem("PSCylinder", [world, canvas, control] {
				control->setWindow(new PSCylinderView("PSCylinder", world, canvas));
				}));

			add(new MenuItem("PSTorus", [world, canvas, control] {
				control->setWindow(new PSTorusView("PSTorus", world, canvas));
				}));
		}
	};

	class WFGenerationMenu : public IMenu
	{
	public:
		WFGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
			IMenu(name, world, canvas)
		{
			add(new MenuItem("WFCircle", [world, canvas, control] {
				control->setWindow(new WFCircleView("WFCircle", world, canvas));
				}));

			add(new MenuItem("WFBox", [world, canvas, control] {
				control->setWindow(new WFBoxView("WFBox", world, canvas));
				}));

			add(new MenuItem("WFCone", [world, canvas, control] {
				control->setWindow(new WFBoxView("WFCone", world, canvas));
				}));

			add(new MenuItem("WFCylinder", [world, canvas, control] {
				control->setWindow(new WFCylinderView("WFCylinder", world, canvas));
				}));

			add(new MenuItem("WFSphere", [world, canvas, control] {
				control->setWindow(new WFSphereView("WFSphere", world, canvas));
				}));

			add(new MenuItem("WFEllipsoid", [world, canvas, control] {
				control->setWindow(new WFEllipsoidView("WFEllipsoid", world, canvas));
				}));

			add(new MenuItem("WFTorus", [world, canvas, control] {
				control->setWindow(new WFTorusView("WFTorus", world, canvas));
				}));
		}
	};

	class PMGenerationMenu : public IMenu
	{
	public:
		PMGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
			IMenu(name, world, canvas)
		{
			add(new MenuItem("PMBox", [world, canvas, control] {
				control->setWindow(new PMBoxView("PMBox", world, canvas));
				}));
			add(new MenuItem("PMQuad", [world, canvas, control] {
				control->setWindow(new PMQuadView("PMQuad", world, canvas));
				}));
			add(new MenuItem("PMSphere", [world, canvas, control] {
				control->setWindow(new PMSphereView("PMSphere", world, canvas));
				}));
			add(new MenuItem("PMCone", [world, canvas, control] {
				control->setWindow(new PMConeView("PMCone", world, canvas));
				}));
		}
	};

	class TMGenerationMenu : public IMenu
	{
	public:
		TMGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
			IMenu(name, world, canvas)
		{
			add(new MenuItem("TMBox", [world, canvas, control] {
				control->setWindow(new TMBoxView("TMBox", world, canvas));
				}));
			//control->setWindow(new PMQuadView("PMQuad", world, canvas));
			add(new MenuItem("TMSphere", [world, canvas, control] {
				control->setWindow(new TMSphereView("TMSphere", world, canvas));
				}));
			//control->setWindow(new PMConeView("PMCone", world, canvas));
		}
	};

	class VolGenerationMenu : public IMenu
	{
	public:
		VolGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
			IMenu(name, world, canvas)
		{
			add(new MenuItem("VolSphere", [world, canvas, control] {
				control->setWindow(new VolSphereView("VolSphere", world, canvas));
				}));
		}
	};

	class VoxelGenerationMenu : public IMenu
	{
	public:
		VoxelGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
			IMenu(name, world, canvas)
		{
			add(new MenuItem("VoxelSphere", [world, canvas, control] {
				control->setWindow(new VoxelSphereView("VoxelSphere", world, canvas));
				}));
		}
	};

	class SolidGenerationMenu : public IMenu
	{
	public:
		SolidGenerationMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
			IMenu(name, world, canvas)
		{
			add(new MenuItem("SolidBox", [world, canvas, control] {
				control->setWindow(new SolidBoxView("SolidBox", world, canvas));
				}));
		}
	};

	class TransformMenu : public IMenu
	{
	public:
		TransformMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
			IMenu(name, world, canvas)
		{
			add(new MenuItem("Scale", [world, canvas, control] {
				control->setWindow(new ScaleView("Scale", world, canvas));
				}));
			add(new MenuItem("Translate", [world, canvas, control] {
				control->setWindow(new TranslateView("Translate", world, canvas));
				}));
			add(new MenuItem("Rotate", [world, canvas, control] {
				control->setWindow(new RotateView("Rotate", world, canvas));
				}));
			add(new MenuItem("Transform", [world, canvas, control] {
				control->setWindow(new TransformView("Transform", world, canvas));
				}));
		}
	};

	class GlobalMenu : public IMenu
	{
	public:
		GlobalMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
			IMenu(name, world, canvas)
		{
			add(new MenuItem("Delete", [world, canvas, control] {
				control->setWindow(new DeleteView("Delete", world, canvas));
				}));
		}
	};
}

ShapeMenu::ShapeMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas)
{
	add(new PSGenerationMenu("ParticleSystem", world, canvas, control));
	add(new WFGenerationMenu("WireFrame", world, canvas, control));
	add(new PMGenerationMenu("PolygonMesh", world, canvas, control));
	add(new TMGenerationMenu("TriangleMesh", world, canvas, control));
	add(new VolGenerationMenu("Volume", world, canvas, control));
	add(new VoxelGenerationMenu("Voxel", world, canvas, control));
	add(new SolidGenerationMenu("Solid", world, canvas, control));
	add(new TransformMenu("Transform", world, canvas, control));
}