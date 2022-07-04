#include "PhysicsMenu.h"

#include "CSPHFluidSimulationView.h"
#include "MVPFluidSimulationView.h"
#include "PBSPHFluidSimulationView.h"
#include "DFSPHFluidSimulationView.h"
#include "MPSFluidSimulationView.h"
#include "SPHFlameSimulationView.h"

#include "MeshBoundaryView.h"
#include "SPHVolumeConverterView.h"
#include "MVPVolumeConverterView.h"
#include "MVPSamplerView.h"

#include "SPHDensityEstimatorView.h"

#include "CrystalScene/AppBase/MenuItem.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PhysicsMenu::PhysicsMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas),
	control(control)
{
	add(new MenuItem("CSPH", [world, canvas, control] {
		control->setWindow(new CSPHFluidSimulationView("CSPHFluid", world, canvas));
		}));

	add(new MenuItem("MVPFluid", [world, canvas, control] {
		control->setWindow(new MVPFluidSimulationView("MVPFluid", world, canvas));
		}));

	add(new MenuItem("MVPSampler", [world, canvas, control] {
		control->setWindow(new MVPSamplerView("MVPSampler", world, canvas));
		}));

	add(new MenuItem("PBSPHFluid", [world, canvas, control] {
		control->setWindow(new PBSPHFluidSimulationView("PBFluid", world, canvas));
		}));

	add(new MenuItem("DFSPHFluid", [world, canvas, control] {
		control->setWindow(new DFSPHFluidSimulationView("DFSPH", world, canvas));
		}));

	add(new MenuItem("MPSFluid", [world, canvas, control] {
		control->setWindow(new MPSFluidSimulationView("MPSFluid", world, canvas));
		}));

	add(new MenuItem("SPHFlame", [world, canvas, control] {
		control->setWindow(new SPHFlameSimulationView("SPHFlame", world, canvas));
		}));
	
	add(new MenuItem("MeshBoundary", [world, canvas, control] {
		control->setWindow(new MeshBoundaryView("Mesh", world, canvas));
		}));

	add(new MenuItem("SPHVolume", [world, canvas, control] {
		control->setWindow(new SPHVolumeConverterView("SPHVolume", world, canvas));
		}));

	add(new MenuItem("MVPVolume", [world, canvas, control] {
		control->setWindow(new MVPVolumeConverterView("MVPVolume", world, canvas));
		}));

	add(new MenuItem("SPHDensity", [world, canvas, control] {
		control->setWindow(new SPHDensityEstimatorView("SPHDensity", world, canvas));
		}));
}