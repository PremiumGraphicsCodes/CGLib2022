#pragma once

#include "CrystalScene/Command/ICommand.h"
#include <vector>

namespace Crystal {
	namespace Space {

class VoxelGetCommand : public Command::ICommand
{
public:
	VoxelGetCommand() :
		Command::ICommand(&args, &results)
	{}

	struct Args : Command::IArgs
	{
		Args();

		Command::Arg< int > voxelId;
	};

	struct Results : Command::IResults
	{
		Results();

		Command::Result< int > resX;
		Command::Result< int > resY;
		Command::Result< int > resZ;
		Command::Result< Math::Box3dd > boundingBox;
		Command::Result< std::vector<bool> > values;
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