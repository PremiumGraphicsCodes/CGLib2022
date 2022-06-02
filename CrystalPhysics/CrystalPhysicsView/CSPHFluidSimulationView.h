#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/FloatView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/DirectoryView.h"
#include "../CrystalPhysics/CSPH/CSPHSolver.h"
#include "../CrystalPhysics/CSPH/CSPHFluidScene.h"

namespace Crystal {
	namespace UI {

class CSPHFluidSimulationView : public IOkCancelView
{
public:
	CSPHFluidSimulationView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void onReset();

private:
	Physics::CSPHFluidScene* fluidScene;
	Physics::CSPHSolver* simulator;
	Button startButton;
	Button resetButton;
	//Button nextButton;
	FloatView pressureCoeView;
	FloatView viscosityView;
	FloatView timeStepView;
	FloatView densityView;
	Box3dView boundaryView;
	DirectoryView outputDirectoryView;
	int newId;
};

	}
}