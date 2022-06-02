#pragma once

#include "CrystalScene/Command/ICommand.h"
#include "Crystal/Math/Vector3d.h"

namespace Crystal {
	namespace Physics {

class PhysicsSolverUpdateCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> id;
		Command::Arg<std::vector<int>> fluidSceneIds;
		Command::Arg<std::vector<int>> emitterSceneIds;
		Command::Arg<std::vector<int>> csgBoundarySceneIds;
		Command::Arg<float> effectLength;
		Command::Arg<float> timeStep;
		Command::Arg<Math::Vector3df> externalForce;
		Command::Arg<Math::Vector3df> buoyancyForce;
		Command::Arg<std::string> name;

		Args();
	};

	struct Results : Command::IResults
	{
		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	PhysicsSolverUpdateCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}