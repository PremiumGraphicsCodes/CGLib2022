#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBSceneVolumeToMeshCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> vdbSceneId;
		Command::Arg<double> threshold;
		Command::Arg<double> adaptivity;
	};

	struct Results : Command::IResults
	{
		Results();

		Command::Result<int> newSceneId;
	};

	VDBSceneVolumeToMeshCommand();

	explicit VDBSceneVolumeToMeshCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}