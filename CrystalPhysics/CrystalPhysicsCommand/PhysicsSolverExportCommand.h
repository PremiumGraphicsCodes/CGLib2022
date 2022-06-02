#pragma once

#include "CrystalScene/Command/ICommand.h"
#include "Crystal/Math/Vector3d.h"

namespace Crystal {
	namespace Physics {

class PhysicsSolverExportCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<std::vector<int>> fluidIds;
		Command::Arg<std::string> filePath;
		Command::Arg<bool> doExportMicro;
		Command::Arg<bool> asBinary;

		Args();
	};

	struct Results : Command::IResults
	{
		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	PhysicsSolverExportCommand();

	explicit PhysicsSolverExportCommand(const Args& args);

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}