#include "MaterialGetCommand.h"

#include "../Scene/MaterialScene.h"

#include "PublicLabel.h"

namespace MaterialGetLabels
{
	PublicLabel CommandNameLabel = "MaterialGet";

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

std::string MaterialGetCommand::getName()
{
	return MaterialGetLabels::CommandNameLabel;
}

MaterialGetCommand::Args::Args() :
	id(MaterialGetLabels::IdLabel, -1)
{
	add(&id);
}

MaterialGetCommand::Results::Results() :
	ambient(MaterialGetLabels::AmbientLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	diffuse(MaterialGetLabels::DiffuseLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	specular(MaterialGetLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	shininess(MaterialGetLabels::ShininessLabel, 1.0f),
//	textureName(MaterialGetLabels::TextureNameLabel, std::string("")),
	name(MaterialGetLabels::NameLabel, std::string(""))
{
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&shininess);
//	add(&textureName);
	add(&name);
}

bool MaterialGetCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<MaterialScene*>(args.id.getValue());
	if (scene == nullptr) {
		return false;
	}
	auto m = scene->getMaterial();
	results.ambient.setValue(Graphics::ColorRGBAf(m->ambient));
	results.diffuse.setValue(Graphics::ColorRGBAf(m->diffuse));
	results.specular.setValue(Graphics::ColorRGBAf(m->specular));
	results.shininess.setValue(m->shininess);
//	results.textureName.setValue(m.ambientTextureName);
	results.name.setValue(scene->getName());

	return true;
}
