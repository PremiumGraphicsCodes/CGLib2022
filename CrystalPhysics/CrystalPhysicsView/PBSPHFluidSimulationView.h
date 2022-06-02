#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/FloatView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/DirectoryView.h"

namespace Crystal {
	namespace Physics {
		class PBFluidScene;
		class PBSPHSolver;
	}
	namespace UI {

class PBSPHFluidSimulationView : public IOkCancelView
{
public:
	PBSPHFluidSimulationView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void onReset();

private:
	Physics::PBSPHSolver* simulator;
	Physics::PBFluidScene* fluidScene;
//	Physics::PBFluidScene* boundaryScene;
	Button startButton;
	Button resetButton;
	FloatView timeStepView;
	FloatView radiusView;
	FloatView effectLengthView;
	FloatView densityView;
	FloatView stiffnessView;
	FloatView vicsocityView;
	Box3dView boundaryView;
};

	}
}