#include "FluidVolumeExportCommand.h"

#include "../CrystalPhysics/FluidVolumeScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"
#include "Crystal/IO/PLYFileWriter.h"

namespace {
	PublicLabel CommandNameLabel = "FluidVolumeExportCommand";
	PublicLabel VolumeIdLabel = "VolumeId";
	PublicLabel FilePathLabel = "FilePath";
}

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string FluidVolumeExportCommand::getName()
{
	return ::CommandNameLabel;
}

FluidVolumeExportCommand::Args::Args() :
	volumeId(::VolumeIdLabel, -1),
	filePath(::FilePathLabel, std::string(""))
{
	add(&volumeId);
	add(&filePath);
}

FluidVolumeExportCommand::Results::Results()
{
}

FluidVolumeExportCommand::FluidVolumeExportCommand() :
	ICommand(&args, &results)
{}

FluidVolumeExportCommand::FluidVolumeExportCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{
}

bool FluidVolumeExportCommand::execute(World* world)
{
	const std::string path = args.filePath.getValue();

	PLYFile file;
	file.properties.push_back(PLYProperty("x", PLYType::INT));
	file.properties.push_back(PLYProperty("y", PLYType::INT));
	file.properties.push_back(PLYProperty("z", PLYType::INT));
	file.properties.push_back(PLYProperty("density", PLYType::FLOAT));

	const int id = args.volumeId.getValue();

	auto volume = world->getScenes()->findSceneById<FluidVolumeScene*>(id);
	if (volume == nullptr) {
		return false;
	}
	const auto nodes = volume->getShape()->getNodes();
	for (const auto n : nodes) {
		const auto i = n->getIndex();
		PLYPoint p;
		p.values.push_back(i[0]);
		p.values.push_back(i[1]);
		p.values.push_back(i[2]);
		p.values.push_back(n->getValue());
		file.vertices.push_back(p);
	}


	PLYFileWriter writer;
	const auto isOk = writer.writeASCII(path, file);
	return isOk;
}
