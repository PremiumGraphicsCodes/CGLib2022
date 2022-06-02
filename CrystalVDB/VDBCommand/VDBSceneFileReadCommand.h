#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBSceneFileReadCommand : public Command::ICommand
{
public:
	struct Args : public Command::IArgs
	{
		Args();

		Command::Arg<float> radius;
		Command::Arg<std::string> filePath;
	};

	struct Results : public Command::IResults
	{
		Results();

		Command::Result<int> newId;
	};

	VDBSceneFileReadCommand();

	explicit VDBSceneFileReadCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

	Results getResults() const { return results; }

private:
	Args args;
	Results results;
};

	}
}