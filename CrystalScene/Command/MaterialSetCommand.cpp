#include "MaterialSetCommand.h"

#include "../Scene/MaterialScene.h"

#include "PublicLabel.h"

namespace MaterialSetLabels
{
	PublicLabel CommandNameLabel = "MaterialSet";

	PublicLabel IdLabel = "Id";
	PublicLabel AmbientLabel = "Ambient";
	PublicLabel DiffuseLabel = "Diffuse";
	PublicLabel SpecularLabel = "Specular";
	PublicLabel ShininessLabel = "Shininess";
	PublicLabel TextureNameLabel = "TextureName";
	PublicLabel NameLabel = "Name";
}

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string MaterialSetCommand::getName()
{
	return MaterialSetLabels::CommandNameLabel;
}

MaterialSetCommand::Args::Args() :
	id(MaterialSetLabels::IdLabel, -1),
	ambient(MaterialSetLabels::AmbientLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	diffuse(MaterialSetLabels::DiffuseLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	specular(MaterialSetLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	shininess(MaterialSetLabels::ShininessLabel, 1.0f),
	//textureName(MaterialSetLabels::TextureNameLabel, std::string("")),
	name(MaterialSetLabels::NameLabel, std::string(""))
{
	add(&id);
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&shininess);
	//add(&textureName);
	add(&name);
}

bool MaterialSetCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<MaterialScene*>(args.id.getValue());
	if (scene == nullptr) {
		return false;
	}
	auto m = scene->getMaterial();
	m->ambient = args.ambient.getValue();
	m->diffuse = args.diffuse.getValue();
	m->specular = args.specular.getValue();
	m->shininess = args.shininess.getValue();
	scene->setName(args.name.getValue());
	return true;
}
