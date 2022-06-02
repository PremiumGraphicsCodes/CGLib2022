#pragma once

#include "ICommand.h"
#include <vector>

namespace Crystal {
	namespace Command {

class PolygonMeshAddFacesCommand : public ICommand
{
public:
	PolygonMeshAddFacesCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< int > meshId;
		Arg< std::vector<int> > vertexIds;
	};

	struct Results : IResults
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