#include "ParticleSystemGetCommand.h"

#include "../Scene/ParticleAttribute.h"
#include "../Scene/ParticleSystemScene.h"

#include "PublicLabel.h"

namespace ParticleSystemGetLabels
{
	PublicLabel CommandNameLabel = "ParticleSystemGet";
	PublicLabel PSIdLabel = "PSId";
	PublicLabel LayerLabel = "Layer";
	PublicLabel PositionsLabel = "Positions";
	PublicLabel PointSizeLabel = "PointSize";
	PublicLabel ColorLabel = "Color";
	PublicLabel NameLabel = "Name";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

ParticleSystemGetCommand::Args::Args() :
	psId(ParticleSystemGetLabels::PSIdLabel, -1),
	layer(ParticleSystemGetLabels::LayerLabel, 1)
{
	add(&psId);
	add(&layer);
}

ParticleSystemGetCommand::Results::Results() :
	positions(ParticleSystemGetLabels::PositionsLabel, {}),
	pointSize(ParticleSystemGetLabels::PointSizeLabel, 1.0f),
	color(ParticleSystemGetLabels::ColorLabel, Graphics::ColorRGBAf(1, 1, 1, 1)),
	name(ParticleSystemGetLabels::NameLabel, std::string(""))
{
	add(&positions);
	add(&pointSize);
	add(&color);
	add(&name);
}

std::string ParticleSystemGetCommand::getName()
{
	return ParticleSystemGetLabels::CommandNameLabel;
}

bool ParticleSystemGetCommand::execute(World* world)
{
	const auto scene = world->getScenes()->findSceneById<IParticleSystemScene*>(args.psId.getValue());
	if (scene == nullptr) {
		return false;
	}

	results.positions.setValue(scene->getPositions());
	results.name.setValue(scene->getName());
	return true;
}
