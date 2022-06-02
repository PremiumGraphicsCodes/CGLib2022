#include "MeshToPSCommand.h"

//#include "PublicLabels/MeshToPSLabels.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

#include "CrystalScene/Scene/PolygonMeshScene.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "../CrystalSpace/MeshToParticleConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Space;
using namespace Crystal::Scene;
using namespace Crystal::Command;


namespace {
	PublicLabel CommandNameLabel = "MeshToPS";
	PublicLabel PolygonMeshIdLabel = "PolygonMeshId";
	PublicLabel DivideLengthLabel = "DivideLength";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
}

MeshToPSCommand::Args::Args() :
	polygonMeshId(::PolygonMeshIdLabel, -1),
	particleSystemId(::ParticleSystemIdLabel, -1),
	divideLength(::DivideLengthLabel, 1.0)
{
	add(&polygonMeshId);
	add(&particleSystemId);
	add(&divideLength);
}

MeshToPSCommand::Results::Results()// :
//	newId(::NewIdLabel, -1)
{
	//	add(&newId);
}

std::string MeshToPSCommand::getName()
{
	return ::CommandNameLabel;
}

bool MeshToPSCommand::execute(World* world)
{
	auto meshScene = world->getScenes()->findSceneById<PolygonMeshScene*>(args.polygonMeshId.getValue());
	if (meshScene == nullptr) {
		return false;
	}

	auto psScene = world->getScenes()->findSceneById<ParticleSystemScene*>(args.particleSystemId.getValue());
	if (psScene == nullptr) {
		return false;
	}

	MeshToParticleConverter converter;
	converter.subdivide(*meshScene->getShape(), args.divideLength.getValue());
	const auto positions = converter.getPositions();

	auto ps = psScene->getShape();
	ParticleAttribute attr;
	attr.color = ColorRGBAf(0, 0, 0, 0);
	for (auto p : positions) {
		ps->add(p, attr);
	}

	return true;
}
