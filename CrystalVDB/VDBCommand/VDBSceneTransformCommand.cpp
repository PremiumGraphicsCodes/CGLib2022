#include "VDBSceneTransformCommand.h"

#include "CrystalScene/Command/Public/PublicLabel.h"
#include "CrystalVDB/CrystalVDB/VDBVolumeScene.h"
#include "CrystalVDB/CrystalVDB/VDBTransform.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneTransform";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
	PublicLabel MatrixLabel = "Matrix";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneTransformCommand::Args::Args() :
	vdbSceneId(::VDBSceneIdLabel, -1),
	matrix(::MatrixLabel, Matrix4dd())
{
	add(&vdbSceneId);
	add(&matrix);
}

VDBSceneTransformCommand::Results::Results()
{
}

VDBSceneTransformCommand::VDBSceneTransformCommand() :
	ICommand(&args, &results)
{}

VDBSceneTransformCommand::VDBSceneTransformCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneTransformCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneTransformCommand::execute(World* world)
{
	/*
	auto volume = world->getScenes()->findSceneById<VDBVolumeScene*>(args.sourceVolumeId.getValue());
	if (volume == nullptr) {
		return false;
	}

	auto target = world->getScenes()->findSceneById<VDBVolumeScene* >(args.targetVolumeId.getValue());
	if (target == nullptr) {
		return false;
	}

	VDBTransform transform;
	transform.transformGeometry();

	return true;
	*/
	return false;
}