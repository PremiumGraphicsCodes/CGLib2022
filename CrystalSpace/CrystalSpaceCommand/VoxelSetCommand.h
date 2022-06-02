#pragma once

#include "CrystalScene/Command/ICommand.h"
#include <vector>

namespace Crystal {
	namespace Space {

class VoxelSetCommand : public Command::ICommand
{
public:
	VoxelSetCommand() :
		Command::ICommand(&args, &results)
	{}

	struct Args : Command::IArgs
	{
		Args();

		Command::Arg< int > voxelId;
		Command::Arg< int > resX;
		Command::Arg< int > resY;
		Command::Arg< int > resZ;
		Command::Arg< Math::Box3dd > bb;
		Command::Arg< std::vector<bool> > values;
	};

	struct Results : Command::IResults
	{
		Results();

		//		Command::Result<int> newId;
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}