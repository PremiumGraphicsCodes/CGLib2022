#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/DoubleView.h"

#include "../CrystalPhysics/MVP/MVPFluidSolver.h"
//#include "../CrystalPhysics/Boundary.h"

namespace Crystal {
	namespace UI {

class MeshBoundaryView : public IOkCancelView
{
public:
	MeshBoundaryView(const std::string& name, Scene::World* model, Canvas* canvas);

	//Physics::Boundary getBoundary() const { return boundary; }

private:
	void onOk() override;

private:
	ObjectSelectView meshSelectView;
	DoubleView divideLengthView;
	//Physics::Boundary boundary;
};

	}
}