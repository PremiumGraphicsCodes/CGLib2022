#include "MaterialCreateCommand.h"

#include "PublicLabel.h"

namespace MaterialCreateLabels
{
	PublicLabel CommandNameLabel = "MaterialCreate";

	PublicLabel AmbientLabel = "Ambient";
	PublicLabel DiffuseLabel = "Diffuse";
	PublicLabel SpecularLabel = "Specular";
	PublicLabel ShininessLabel = "Shininess";
	PublicLabel AmbientTextureNameLabel = "AmbientTextureName";
	PublicLabel DiffuseTextureNameLabel = "DiffuseTextureName";
	PublicLabel SpecularTextureNameLabel = "SpecularTextureName";

	PublicLabel NameLabel = "Name";

	PublicLabel NewIdLabel = "NewId";
}

#include "../Scene/MaterialScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string MaterialCreateCommand::getName()
{
	return MaterialCreateLabels::CommandNameLabel;
}

MaterialCreateCommand::Args::Args() :
	ambient(MaterialCreateLabels::AmbientLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	diffuse(MaterialCreateLabels::DiffuseLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	specular(MaterialCreateLabels::SpecularLabel, Graphics::ColorRGBAf(0, 0, 0, 0)),
	shininess(MaterialCreateLabels::ShininessLabel, 1.0f),
	ambientTextureName(MaterialCreateLabels::AmbientTextureNameLabel, std::string("")),
	diffuseTextureName(MaterialCreateLabels::DiffuseTextureNameLabel, std::string("")),
	specularTextureName(MaterialCreateLabels::SpecularTextureNameLabel, std::string("")),
	name(MaterialCreateLabels::NameLabel, std::string(""))
{
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&shininess);
	add(&ambientTextureName);
	add(&diffuseTextureName);
	add(&specularTextureName);
	add(&name);
}

MaterialCreateCommand::Results::Results() :
	newId(MaterialCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

bool MaterialCreateCommand::execute(World* world)
{
	auto m = std::make_unique<Material>();

	m->ambient = args.ambient.getValue();
	m->diffuse = args.diffuse.getValue();
	m->specular = args.specular.getValue();
	m->shininess = args.shininess.getValue();

	//m.ambientTextureName = args.ambientTextureName.getValue();
	//m.diffuseTextureName = args.diffuseTextureName.getValue();
	//m.specularTextureName = args.specularTextureName.getValue();

	auto scene = new MaterialScene(world->getNextSceneId(), "BlackMat", std::move(m) );
	world->getScenes()->addScene(scene);

	scene->getPresenter()->createView(world->getRenderer());

	results.newId.setValue(scene->getId());

	return true;
}
