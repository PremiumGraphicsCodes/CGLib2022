#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/FloatView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/ComboBox.h"

#include "../CrystalPhysics/SPHFlame/SPHFlameParticle.h"
#include "../CrystalPhysics/SPHFlame/SPHFlameSolver.h"
#include "../CrystalPhysics/SPHFlame/SPHFlameScene.h"


namespace Crystal {
	namespace UI {

class SPHFlameSimulationView : public IOkCancelView
{
public:
	SPHFlameSimulationView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void onReset();

private:
	Physics::SPHFlameScene* flame;
	Physics::SPHFlameScene* heatSource;
	Physics::SPHFlameSolver* solver;
	Button startButton;
	Button resetButton;
	FloatView pressureCoeView;
	FloatView viscosityView;
	FloatView timeStepView;
	FloatView densityView;
	Box3dView boundaryView;
	ComboBox presenterView;
};

	}
}