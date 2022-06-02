#include "TXTFileExportCommand.h"

#include "../../Crystal/IO/TXTFileWriter.h"
#include "../Scene/ParticleSystemScene.h"

#include "PublicLabel.h"

namespace TXTFileExportLabels
{
	PublicLabel CommandNameLabel = "TXTFileExport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel IdsLabel = "Ids";
}

using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::IO;

TXTFileExportCommand::Args::Args() :
	ids(TXTFileExportLabels::IdsLabel, {}),
	filePath(TXTFileExportLabels::FilePathLabel, "")
{
	add(&ids);
	add(&filePath);
}

TXTFileExportCommand::Results::Results()
{
	//	add(&isOk);
}

std::string TXTFileExportCommand::getName()
{
	return TXTFileExportLabels::CommandNameLabel;
}

bool TXTFileExportCommand::execute(World* world)
{
	const auto ids = args.ids.getValue();

	TXTFileWriter writer;
	for (const auto id : ids) {
		auto scene = world->getScenes()->findSceneById<IParticleSystemScene*>(id);
		if (scene == nullptr) {
			continue;
		}
		const auto& ps = scene->getPositions();
		for (const auto& p : ps) {
			writer.add(p);
		}
	}

	const auto isOk = writer.write(args.filePath.getValue());
	return isOk;
}
