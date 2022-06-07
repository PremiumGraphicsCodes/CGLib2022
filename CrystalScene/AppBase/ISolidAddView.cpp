#include "ISolidAddView.h"

#include "../Scene/SolidScene.h"

#include "../Command/Command.h"
#include "../Command/ShaderBuildCommand.h"
//#include "../Command/CameraL.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

ISolidAddView::ISolidAddView(const std::string& name, Scene::World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
//	attributeView("WFAttribute"),
	nameView("Name", "WireFrame01"),
	colorView("Color", ColorRGBAf(1,1,1,0))
{
	//add(&attributeView);
	add(&nameView);
	add(&colorView);
}

void ISolidAddView::addSolid(std::unique_ptr<Solid> solid)
{
	const auto& name = nameView.getValue();
	auto newId = getWorld()->getNextSceneId();
	auto scene = new SolidScene(newId, name, std::move(solid));
	scene->setColor(colorView.getValue());
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer());
}
