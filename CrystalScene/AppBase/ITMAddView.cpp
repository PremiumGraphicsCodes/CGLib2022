#include "ITMAddView.h"

#include "../Scene/TriangleMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

ITMAddView::ITMAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	nameView("Name", "PolygonMesh01")//,
	//materialView("Material", model),
	//presenterView("Presenter")
{
	add(&nameView);
	//add(&materialView);
	//add(&presenterView);
}

void ITMAddView::addTriangleMesh(std::unique_ptr<TriangleMesh> shape)
{
	auto world = getWorld();

	auto scene = new TriangleMeshScene(world->getNextSceneId(), nameView.getValue(), std::move(shape));
	world->getScenes()->addScene(scene);

	//presenterView.setPresenter(scene, world);

	scene->getPresenter()->createView(getWorld()->getRenderer());
}