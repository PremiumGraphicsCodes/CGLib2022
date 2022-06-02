#include "LightSetCommand.h"

#include "PublicLabel.h"

namespace LightSetLabels
{
	PublicLabel CommandNameLabel = "LightSet";

	PublicLabel IdLabel = "Id";
	PublicLabel PositionLabel = "Position";
	PublicLabel AmbientLabel = "Ambient";
	PublicLabel DiffuseLabel = "Diffuse";
	PublicLabel SpecularLabel = "Specular";
	PublicLabel NameLabel = "Name";
}

#include "../Scene/LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string LightSetCommand::getName()
{
	return LightSetLabels::CommandNameLabel;
}

LightSetCommand::Args::Args() :
	id(LightSetLabels::IdLabel, -1),
	position(LightSetLabels::PositionLabel, Vector3dd(0, 0, 0)),
	ambient(LightSetLabels::AmbientLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	diffuse(LightSetLabels::DiffuseLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	specular(LightSetLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	name(LightSetLabels::NameLabel, std::string(""))
{
	add(&id);
	add(&position);
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&name);
}

bool LightSetCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<LightScene*>(args.id.getValue());
	if (scene == nullptr) {
		return false;
	}
	auto l = scene->getLight();
	l->setPosition(args.position.getValue());
	l->setAmbient(args.ambient.getValue());
	l->setDiffuse(args.diffuse.getValue());
	l->setSpecular(args.specular.getValue());
	scene->setName(args.name.getValue());
	return true;
}
