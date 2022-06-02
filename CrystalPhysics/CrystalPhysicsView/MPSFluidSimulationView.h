#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/FloatView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "../CrystalPhysics/MPS/MPSFluidSolver.h"
#include "../CrystalPhysics/MPS/MPSFluidScene.h"

namespace Crystal {
	namespace UI {

class MPSFluidSimulationView : public IOkCancelView
{
public:
	MPSFluidSimulationView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void onReset();

private:
	Physics::MPSFluidScene* fluidScene;
	Physics::MPSFluidSolver* simulator;
	Button startButton;
	Button resetButton;
	FloatView pressureCoeView;
	FloatView viscosityView;
	FloatView timeStepView;
	FloatView densityView;
	Box3dView boundaryView;
};

	}
}