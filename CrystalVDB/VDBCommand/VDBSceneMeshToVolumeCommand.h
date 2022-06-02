#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBSceneMeshToVolumeCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> vdbSceneId;
		Command::Arg<double> divideLength;
	};

	struct Results : Command::IResults
	{
		Results();

		Command::Arg<int> newSceneId;
	};

	VDBSceneMeshToVolumeCommand();

	explicit VDBSceneMeshToVolumeCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}