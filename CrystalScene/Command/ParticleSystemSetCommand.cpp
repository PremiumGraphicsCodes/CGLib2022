#include "ParticleSystemSetCommand.h"

#include "../Scene/ParticleAttribute.h"
#include "../Scene/ParticleSystemScene.h"

#include "PublicLabel.h"

namespace ParticleSystemSetLabels
{
	PublicLabel CommandNameLabel = "ParticleSystemSet";
	PublicLabel IdLabel = "Id";
	PublicLabel PositionsLabel = "Positions";
	PublicLabel PointSizeLabel = "PointSize";
	PublicLabel ColorLabel = "Color";
	PublicLabel NameLabel = "Name";
	PublicLabel LayerLabel = "Layer";
	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

ParticleSystemSetCommand::Args::Args() :
	psId(ParticleSystemSetLabels::IdLabel, -1),
	positions(ParticleSystemSetLabels::PositionsLabel, {}),
	pointSize(ParticleSystemSetLabels::PointSizeLabel, 1.0f),
	color(ParticleSystemSetLabels::ColorLabel, Graphics::ColorRGBAf(1, 1, 1, 1)),
	name(ParticleSystemSetLabels::NameLabel, std::string(""))
{
	add(&psId);
	add(&positions);
	add(&pointSize);
	add(&color);
	add(&name);
}

ParticleSystemSetCommand::Results::Results()
{
}

std::string ParticleSystemSetCommand::getName()
{
	return ParticleSystemSetLabels::CommandNameLabel;
}

bool ParticleSystemSetCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<ParticleSystemScene*>(args.psId.getValue());
	if (scene == nullptr) {
		return false;
	}
	const auto& positions = args.positions.getValue();
	ParticleAttribute attr;
	attr.color = args.color.getValue();
	attr.size = args.pointSize.getValue();
	auto name = args.name.getValue();
	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
	scene->resetShape(std::move(shape));
	return true;
}
