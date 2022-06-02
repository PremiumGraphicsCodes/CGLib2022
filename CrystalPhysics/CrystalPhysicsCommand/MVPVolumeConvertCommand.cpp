#include "MVPVolumeConvertCommand.h"

#include "Crystal/Shape/IParticleSystem.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

#include "CrystalPhysics/CrystalPhysics/MVPVolumeConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
//using namespace Crystal::Space;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

namespace {
	PublicLabel CommandNameLabel = "MVPVolumeConvertCommand";
	PublicLabel VolumeParticleSystemIdLabel = "VolumeParticleSystemId";
	PublicLabel MassParticleSystemIdLabel = "MassParticleSystemId";
	PublicLabel TriangleMeshIdLabel = "TriangleMeshId";
	PublicLabel ParticleRadiusLabel = "ParticleRadius";
	PublicLabel ThresholdLabel = "Threshold";
}

std::string MVPVolumeConvertCommand::getName()
{
	return ::CommandNameLabel;
}

MVPVolumeConvertCommand::Args::Args() :
	volumeParticleSystemId(::VolumeParticleSystemIdLabel, -1),
	massParticleSystemId(::MassParticleSystemIdLabel, -1),
	triangleMeshId(::TriangleMeshIdLabel, -1),
	particleRadius(::ParticleRadiusLabel, 1.0),
	threshold(::ThresholdLabel, 1.0f)
{
	add(&volumeParticleSystemId);
	add(&massParticleSystemId);
	add(&triangleMeshId);
	add(&particleRadius);
	add(&threshold);
}

MVPVolumeConvertCommand::Results::Results()// :
//	newId(::NewIdLabel, 0)
{
	//	add(&newId);
}

MVPVolumeConvertCommand::MVPVolumeConvertCommand() :
	ICommand(&args, &results)
{}

bool MVPVolumeConvertCommand::execute(World* world)
{
	auto volumeParticles = world->getScenes()->findSceneById<IParticleSystemScene*>(args.volumeParticleSystemId.getValue());
	if (volumeParticles == nullptr) {
		return false;
	}
	auto massParticles = world->getScenes()->findSceneById<IParticleSystemScene*>(args.massParticleSystemId.getValue());
	if (massParticles == nullptr) {
		return false;
	}
	auto tm = world->getScenes()->findSceneById<TriangleMeshScene*>(args.triangleMeshId.getValue());
	if (tm == nullptr) {
		return false;
	}

	/*
	MVPVolumeConverter builder;
	builder.buildVolumes(volumeParticles->getPositions(), args.particleRadius.getValue(), 1);
	builder.buildMasses(massParticles->getPositions(), args.particleRadius.getValue());
	*/

	/*
	auto mesh = std::make_unique<TriangleMesh>();
	const auto triangles = builder.getTriangles();
	for (const auto& t : triangles) {
		mesh->addFace(TriangleFace(t));
	}
	tm->setShape(std::move(mesh));
	*/

	return true;
}