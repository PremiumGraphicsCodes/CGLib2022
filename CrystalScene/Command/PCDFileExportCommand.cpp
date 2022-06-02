#include "PCDFileExportCommand.h"

#include "../../Crystal/IO/PCDFileWriter.h"
#include "../Scene/ParticleSystemScene.h"

#include "PublicLabel.h"

namespace PCDFileExportLabels
{
	PublicLabel CommandNameLabel = "PCDFileExport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel IdsLabel = "Ids";
	PublicLabel IsBinaryLabel = "IsBinary";
}

using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::IO;

PCDFileExportCommand::Args::Args() :
	ids(PCDFileExportLabels::IdsLabel, {}),
	filePath(PCDFileExportLabels::FilePathLabel, "")
{
	add(&ids);
	add(&filePath);
}

PCDFileExportCommand::Results::Results()
{
//	add(&isOk);
}

std::string PCDFileExportCommand::getName()
{
	return PCDFileExportLabels::CommandNameLabel;
}

bool PCDFileExportCommand::execute(World* world)
{
	const auto& ids = args.ids.getValue();
	auto scenes = world->getScenes()->findScenes(SceneTypeLabels::ParticleSystemScene);

	PCDFile file;
	for (const auto& id : ids) {
		auto scene = world->getScenes()->findSceneById<ParticleSystemScene*>(id);
		const auto& ps = scene->getShape()->getParticles();
		for (auto p : ps) {
			file.data.positions.push_back(p->getPosition());
		}
	}
	file.header.width = static_cast<int>( file.data.positions.size() );
	file.header.points = static_cast<int>( file.data.positions.size() );
	PCDFileWriter writer;
	std::filesystem::path filePath(args.filePath.getValue());
	const auto isOk = writer.writeAscii(filePath, file);
	//this->results.isOk.setValue( isOk );
	return isOk;
}
