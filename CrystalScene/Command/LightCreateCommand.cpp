#include "LightCreateCommand.h"

#include "PublicLabel.h"

namespace LightCreateLabels
{
	PublicLabel CommandNameLabel = "LightCreate";

	PublicLabel PositionLabel = "Position";
	PublicLabel AmbientLabel = "Ambient";
	PublicLabel DiffuseLabel = "Diffuse";
	PublicLabel SpecularLabel = "Specular";
	PublicLabel NameLabel = "Name";

	PublicLabel NewIdLabel = "NewId";
}

#include "../Scene/LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string LightCreateCommand::getName()
{
	return LightCreateLabels::CommandNameLabel;
}

LightCreateCommand::Args::Args() :
	position(LightCreateLabels::PositionLabel, Vector3dd(0,0,0)),
	ambient(LightCreateLabels::AmbientLabel, Graphics::ColorRGBAf(0,0,0,0)),
	diffuse(LightCreateLabels::DiffuseLabel, Graphics::ColorRGBAf(0,0,0,0)),
	specular(LightCreateLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	name(LightCreateLabels::NameLabel, std::string(""))
{
	add(&position);
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&name);
}

LightCreateCommand::Results::Results() :
	newId(LightCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

bool LightCreateCommand::execute(World* world)
{
	auto l = std::make_unique<PointLight>();
	l->setPosition(args.position.getValue());
	l->setAmbient(args.ambient.getValue());
	l->setDiffuse(args.diffuse.getValue());
	l->setSpecular(args.specular.getValue());
//	auto scene = world->getSceneFactory()->createLightScene(std::move(l), args.name.getValue());
	auto scene = new LightScene(world->getNextSceneId(), args.name.getValue(), std::move(l));
	world->getScenes()->addScene(scene);
	results.newId.setValue(scene->getId());
	return true;
}
