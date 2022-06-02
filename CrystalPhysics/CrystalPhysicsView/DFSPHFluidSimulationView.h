#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/FloatView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "../CrystalPhysics/DFSPH/DFFluidSolver.h"

namespace Crystal {
	namespace Physics {
		class DFFluidScene;
		class DFFluidSolver;
	}
	namespace UI {

class DFSPHFluidSimulationView : public IOkCancelView
{
public:
	DFSPHFluidSimulationView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void reset();

private:
	Physics::DFFluidSolver* simulator;
	Physics::DFFluidScene* fluidScene;
	Physics::DFFUpdater updater;
	Button startButton;
	Button resetButton;
	FloatView timeStepView;
	FloatView viscosityCoeView;
	Box3dView boundaryView;
	int newId;
};

	}
}