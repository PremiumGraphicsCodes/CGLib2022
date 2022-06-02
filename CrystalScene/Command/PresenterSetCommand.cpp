#include "PresenterSetCommand.h"

#include "../Scene/PolygonMeshScene.h"
#include "../Scene/PMSmoothPresenter.h"
#include "../Scene/PMWirePresenter.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

//#include "ShaderSendCommand.h"

#include "PublicLabel.h"

namespace PresenterSetLabels
{
	PublicLabel CommandNameLabel = "PresenterSet";

	PublicLabel IdLabel = "Id";
	PublicLabel PresenterNameLabel = "PresenterName";
}

PresenterSetCommand::Args::Args() :
	id(PresenterSetLabels::IdLabel, 0),
	presenterName(PresenterSetLabels::PresenterNameLabel, std::string(""))
{
	add(&id);
}

std::string PresenterSetCommand::getName()
{
	return PresenterSetLabels::CommandNameLabel;
}

bool PresenterSetCommand::execute(World* world)
{
	auto s = world->getScenes()->findSceneById(std::any_cast<int>(args.id.getValue()));
	if (s->getType() == SceneTypeLabels::PolygonMeshScene) {
		auto scene = static_cast<PolygonMeshScene*>(s);
		const auto name = args.presenterName.getValue();
		scene->getPresenter()->removeView(world->getRenderer());
		if (name == "Smooth") {
			auto presenter = std::make_unique<PMSmoothPresenter>(scene);
			scene->setPresenter(std::move(presenter));
		}
		else if (name == "Wire") {
			auto presenter = std::make_unique<PMWirePresenter>(scene);
			scene->setPresenter(std::move(presenter));
		}
		scene->getPresenter()->createView(world->getRenderer());
	}
	return true;
}