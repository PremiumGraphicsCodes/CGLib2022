#include "SparseVolumeNodeSetCommand.h"

#include "../CrystalSpace/SparseVolumeScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "SparseVolumeNodeSet";
	PublicLabel SparseVolumeIdLabel = "SparseVolumeId";
	PublicLabel IndicesXLabel = "IndicesX";
	PublicLabel IndicesYLabel = "IndicesY";
	PublicLabel IndicesZLabel = "IndicesZ";
	PublicLabel ValuesLabel = "Values";
}


using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Scene;
using namespace Crystal::Command;

SparseVolumeNodeSetCommand::Args::Args() :
	sparseVolumeId(::SparseVolumeIdLabel, -1),
	indicesX(::IndicesXLabel, { 0 }),
	indicesY(::IndicesYLabel, { 0 }),
	indicesZ(::IndicesZLabel, { 0 }),
	values(::ValuesLabel, { 0.0f })
{
	add(&sparseVolumeId);
	add(&indicesX);
	add(&indicesY);
	add(&indicesZ);
	add(&values);
}

SparseVolumeNodeSetCommand::Results::Results()// :
//	newId(::NewIdLabel, -1)
{
//	add(&newId);
}

std::string SparseVolumeNodeSetCommand::getName()
{
	return ::CommandNameLabel;
}

bool SparseVolumeNodeSetCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<SparseVolumeScene*>(args.sparseVolumeId.getValue());
	if (scene == nullptr) {
		return false;
	}

	auto shape = scene->getShape();

	const auto indicesx = args.indicesX.getValue();
	const auto indicesy = args.indicesY.getValue();
	const auto indicesz = args.indicesZ.getValue();
	const auto values = args.values.getValue();

	assert(indicesx.size() == indicesy.size());
	assert(indicesy.size() == indicesz.size());
	assert(indicesz.size() == values.size());

	for (int i = 0; i < indicesx.size(); ++i) {
		std::array<int, 3> index({ indicesx[i], indicesy[i], indicesz[i] });
		auto n = shape->createNode(index);
		n->setValue(values[i]);
	}

	return true;
}
