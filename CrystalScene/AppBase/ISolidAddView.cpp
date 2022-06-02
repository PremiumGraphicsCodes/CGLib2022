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
	colorView("Color", ColorRGBAf(0,0,0,0))
{
	//add(&attributeView);
	add(&nameView);
}

void ISolidAddView::addSolid(std::unique_ptr<Solid> solid)
{
	/*
	auto newId = getWorld()->getNextSceneId();
	auto scene = new SolidScene(newId, name, std::move(solid));
	scene->setColor(colorView.getValue());
	getWorld()->getScenes()->addScene(scene);
	//getWorld()->addScene(scene);


	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
	*/
}
