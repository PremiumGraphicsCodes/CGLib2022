#include "TXTFileImportCommand.h"

#include "../../Crystal/IO/TXTFileReader.h"
#include "../Scene/ParticleSystemScene.h"

#include "PublicLabel.h"

namespace TXTFileImportLabels
{
	PublicLabel CommandNameLabel = "TXTFileImport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel IdLabel = "Id";
}

using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TXTFileImportCommand::Args::Args() :
	filePath(TXTFileImportLabels::FilePathLabel, ""),
	id(TXTFileImportLabels::IdLabel, -1)
{
	add(&filePath);
	add(&id);
}

TXTFileImportCommand::Results::Results()
{
}

std::string TXTFileImportCommand::getName()
{
	return TXTFileImportLabels::CommandNameLabel;
}

bool TXTFileImportCommand::execute(Crystal::Scene::World* world)
{
	TXTFileReader reader;
	const auto isOk = reader.read(args.filePath.getValue());

	if (!isOk) {
		return false;
	}
	const auto& positions = reader.getPositions();

	auto scene = world->getScenes()->findSceneById<ParticleSystemScene*>(args.id.getValue());
	if (scene == nullptr) {
		return false;
	}

	ParticleAttribute attr;
	auto ps = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
	scene->resetShape(std::move(ps));
	return true;
}