#pragma once

#include "ICommand.h"
#include "Crystal/Math/Vector3d.h"
#include "Crystal/Math/Triangle3d.h"

#include <vector>
#include <string>

namespace Crystal {
	namespace Command {

class TriangleMeshSetCommand : public ICommand
{
public:
	TriangleMeshSetCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< int > meshId;

		Arg< std::vector<Math::Triangle3d> > triangles;
		//Arg< std::vector<Math::Vector3dd>> normals;
		//Arg< std::string > name;
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