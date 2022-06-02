#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Triangle3d.h"
#include <vector>

namespace Crystal {
	namespace Command {

class TriangleMeshCreateCommand : public ICommand
{
public:
	TriangleMeshCreateCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< std::vector<Math::Triangle3d> > triangles;
		Arg< std::string > name;
	};

	struct Results : IResults
	{
		Results();

		Result<int> newId;
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