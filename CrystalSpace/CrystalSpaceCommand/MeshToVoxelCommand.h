#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace Space {

class MeshToVoxelCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> meshId;
		Command::Arg<int> voxelId;
		Command::Arg<double> divideLength;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	MeshToVoxelCommand();

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}