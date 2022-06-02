#include "PLYFileExportCommand.h"

#include "../../Crystal/IO/PLYFileWriter.h"
#include "../Scene/ParticleSystemScene.h"

#include "PublicLabel.h"

namespace PLYFileExportLabels
{
	PublicLabel CommandNameLabel = "PLYFileExport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel IdsLabel = "Ids";
	PublicLabel IsBinaryLabel = "IsBinary";
}

using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::IO;

PLYFileExportCommand::Args::Args() :
	ids(PLYFileExportLabels::IdsLabel, {}),
	filePath(PLYFileExportLabels::FilePathLabel, ""),
	isBinary(PLYFileExportLabels::IsBinaryLabel, false)
{
	add(&ids);
	add(&filePath);
	add(&isBinary);
}

PLYFileExportCommand::Results::Results()
{
	//	add(&isOk);
}

std::string PLYFileExportCommand::getName()
{
	return PLYFileExportLabels::CommandNameLabel;
}

bool PLYFileExportCommand::execute(World* world)
{
	const auto& ids = args.ids.getValue();
	auto scenes = world->getScenes()->findScenes(SceneTypeLabels::ParticleSystemScene);

	PLYFile file;
	for (const auto& id : ids) {
		auto scene = world->getScenes()->findSceneById<ParticleSystemScene*>(id);
		const auto& ps = scene->getShape()->getParticles();
		for (auto p : ps) {
			auto pp = p->getPosition();
			PLYPoint ppp;
			ppp.values.push_back(pp[0]);
			ppp.values.push_back(pp[1]);
			ppp.values.push_back(pp[2]);
			file.vertices.push_back(ppp);
		}
	}
	PLYFileWriter writer;
	std::filesystem::path filePath(args.filePath.getValue());
	const auto isOk = writer.writeBinary(filePath, file);
	//this->results.isOk.setValue( isOk );
	return isOk;
}
