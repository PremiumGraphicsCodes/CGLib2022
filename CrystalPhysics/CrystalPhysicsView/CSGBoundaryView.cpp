#include "CSGBoundaryView.h"

#include "../CrystalPhysics/Boundary/CSGBoundaryScene.h"
#include "CrystalScene/Scene/World.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Physics;

CSGBoundaryView::CSGBoundaryView(const std::string& name, Scene::World* model) :
	IView(name),
	boxView("Box"),
	world(model)
{
	add(&boxView);

	boxView.setValue(Box3d(Vector3dd(0, 0.0, 0.0), Vector3dd(100.0, 1000.0, 40.0)));

	boundary = std::make_unique<CSGBoundaryScene>(-1, "CSGBoundary");
	boundary->add(boxView.getValue());
}

CSGBoundaryScene* CSGBoundaryView::getBoundary() const
{
	boundary->clearBoxes();
	boundary->add(boxView.getValue());
	//boundary->getPresenter()->createView(world->getRenderer());

	return boundary.get();
}