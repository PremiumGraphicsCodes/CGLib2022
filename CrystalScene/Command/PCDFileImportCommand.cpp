#include "PCDFileImportCommand.h"

#include "../../Crystal/IO/PCDFileReader.h"
#include "../Scene/ParticleSystemScene.h"

#include "PublicLabel.h"

namespace PCDFileImportLabels
{
	PublicLabel CommandNameLabel = "PCDFileImport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
}

using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PCDFileImportCommand::Args::Args() :
	filePath(PCDFileImportLabels::FilePathLabel, ""),
	particleSystemId(PCDFileImportLabels::ParticleSystemIdLabel, -1)
{
	add(&filePath);
	add(&particleSystemId);
}

PCDFileImportCommand::Results::Results()
{
}

std::string PCDFileImportCommand::getName()
{
	return PCDFileImportLabels::CommandNameLabel;
}

bool PCDFileImportCommand::execute(Crystal::Scene::World* scene)
{
	const auto id = args.particleSystemId.getValue();
	const auto filePath = args.filePath.getValue();
	const auto psScene = scene->getScenes()->findSceneById<ParticleSystemScene*>(id);
	if (psScene == nullptr) {
		return false;
	}

	PCDFileReader reader;
	const auto isOk = reader.readBinary(args.filePath.getValue());
	if (!isOk) {
		return false;
	}
	const auto& positions = reader.getPCD().data.positions;
	ParticleAttribute attr;
	attr.color = glm::vec4(0, 0, 0, 0);
	attr.size = 1.0;
	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
	psScene->resetShape(std::move(shape));
	return true;
}