#include "SPHVolumeConvertCommand.h"

//#include "../CrystalPhysics/KFFluidScene.h"
#include "CrystalScene/Scene/IParticleSystemScene.h"
#include "CrystalPhysics/CrystalPhysics/FluidVolumeScene.h"
#include "CrystalPhysics/CrystalPhysics/SurfaceConstruction/SPHVolumeConverter.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "SPHVolumeConvertCommand";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
	PublicLabel VolumeIdLabel = "VolumeId";
	PublicLabel ParticleRadiusLabel = "ParticleRadius";
	PublicLabel CellLengthLabel = "CellLength";
	PublicLabel ThresholdLabel = "Threshold";
	PublicLabel IsIsotropicLabel = "IsIsotoropic";
}


using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string SPHVolumeConvertCommand::getName()
{
	return ::CommandNameLabel;
}

SPHVolumeConvertCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	volumeId(::VolumeIdLabel, -1),
	particleRadius(::ParticleRadiusLabel, 1.0),
	cellLength(::CellLengthLabel, 1.0),
	isIsotorpic(::IsIsotropicLabel, true)
{
	add(&particleSystemId);
	add(&volumeId);
	add(&particleRadius);
	add(&cellLength);
	add(&isIsotorpic);
}

SPHVolumeConvertCommand::Results::Results()// :
//	newId(::NewIdLabel, 0)
{
//	add(&newId);
}

SPHVolumeConvertCommand::SPHVolumeConvertCommand() :
	ICommand(&args, &results)
{}

SPHVolumeConvertCommand::SPHVolumeConvertCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

bool SPHVolumeConvertCommand::execute(World* world)
{
	auto ps = world->getScenes()->findSceneById<IParticleSystemScene*>(args.particleSystemId.getValue());
	if (ps == nullptr) {
		return false;
	}
	auto sp = world->getScenes()->findSceneById<FluidVolumeScene*>(args.volumeId.getValue());
	if (sp == nullptr) {
		return false;
	}

	const auto positions = ps->getPositions();

	const auto particleRadius = args.particleRadius.getValue();
	const auto cellLength = args.cellLength.getValue();

	SPHVolumeConverter builder;
	std::unique_ptr<SparseVolumed> volume;
	if (args.isIsotorpic.getValue()) {
		auto shape = builder.buildIsotoropic(positions, particleRadius, cellLength);
		if (shape != nullptr) {
			sp->resetShape(std::move(shape));
		}
	}
	else {
		auto shape = builder.buildAnisotoropic(positions, args.particleRadius.getValue(), cellLength);
		if (shape != nullptr) {
			sp->resetShape(std::move(shape));
		}
	}

	return true;
}