#include "IWFAddView.h"

#include "../Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

IWFAddView::IWFAddView(const std::string& name, Scene::World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	attributeView("WFAttribute"),
	nameView("Name", "WireFrame01")
{
	add(&attributeView);
	add(&nameView);
}

void IWFAddView::addWireFrame(const std::vector<Vector3dd>& positions, const std::vector<WireFrameEdge>& edges)
{
	WireFrameAttribute attr = attributeView.getValue();
	const auto& name = nameView.getValue();
	auto shape = std::make_unique<WireFrame>(positions, edges);
	auto newId = getWorld()->getNextSceneId();
	auto scene = new WireFrameScene(newId, name, std::move(shape), attr);
	getWorld()->getScenes()->addScene(scene);
	//getWorld()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer());
}
