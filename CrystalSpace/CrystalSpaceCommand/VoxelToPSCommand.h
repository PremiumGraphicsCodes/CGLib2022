#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace Space {

class VoxelToPSCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> voxelId;
		Command::Arg<int> psId;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VoxelToPSCommand();

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}