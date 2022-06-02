#pragma once

#include "CrystalScene/AppBase/IView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/Button.h"
#include "../CrystalPhysics/Boundary/CSGBoundaryScene.h"

namespace Crystal {
	namespace Scene {
		class World;
	}
	namespace UI {

class CSGBoundaryView : public IView
{
public:
	explicit CSGBoundaryView(const std::string& name, Scene::World* model);

	Physics::CSGBoundaryScene* getBoundary() const;// { return boundary.get(); }

private:
	Scene::World* world;
	Box3dView boxView;
	std::unique_ptr<Physics::CSGBoundaryScene> boundary;
};

	}
}