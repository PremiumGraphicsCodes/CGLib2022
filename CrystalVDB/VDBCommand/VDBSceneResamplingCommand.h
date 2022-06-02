#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBSceneResamplingCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> sceneId;
		Command::Arg<std::string> samplingType;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBSceneResamplingCommand();

	explicit VDBSceneResamplingCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}