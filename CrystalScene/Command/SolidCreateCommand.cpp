#include "SolidCreateCommand.h"

#include "../Scene/SolidScene.h"

#include "PublicLabel.h"

namespace SolidCreateLabels
{
	PublicLabel ParticleSystemAddLabel = "SolidCreate";
	PublicLabel BoxLabel = "Box";
	PublicLabel ColorLabel = "Color";
	PublicLabel NameLabel = "Name";
	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

SolidCreateCommand::Args::Args() :
	box(SolidCreateLabels::BoxLabel, Box3dd()),
	color(SolidCreateLabels::ColorLabel, Graphics::ColorRGBAf(1, 1, 1, 1)),
	name(SolidCreateLabels::NameLabel, std::string(""))
{
	add(&box);
	add(&color);
	add(&name);
}

SolidCreateCommand::Results::Results() :
	newId(SolidCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string SolidCreateCommand::getName()
{
	return SolidCreateLabels::ParticleSystemAddLabel;
}

bool SolidCreateCommand::execute(World* world)
{
	const auto& box = args.box.getValue();
	const auto color = args.color.getValue();
	auto name = args.name.getValue();
	auto solid3d = std::make_unique<Crystal::Math::Box3dd>();
	(*solid3d) = box;
	std::unique_ptr< Crystal::Shape::Solid > solid = std::make_unique<Crystal::Shape::Solid>((std::move(solid3d)));
	auto scene = new SolidScene(world->getNextSceneId(), name, std::move(solid));
	world->addScene(scene);
	results.newId.setValue(scene->getId());
	return true;
}
