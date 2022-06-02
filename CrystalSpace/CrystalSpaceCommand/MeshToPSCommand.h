#pragma once

#include "CrystalScene/Command/ICommand.h"
#include <vector>

namespace Crystal {
	namespace Space {

class MeshToPSCommand : public Command::ICommand
{
public:
	MeshToPSCommand() :
		Command::ICommand(&args, &results)
	{}

	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> polygonMeshId;
		Command::Arg<int> particleSystemId;
		Command::Arg<float> divideLength;
	};

	struct Results : Command::IResults
	{
		Results();

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