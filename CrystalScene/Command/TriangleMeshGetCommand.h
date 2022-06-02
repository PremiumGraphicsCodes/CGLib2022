#pragma once

#include "ICommand.h"
#include "Crystal/Math/Vector3d.h"
#include "Crystal/Math/Triangle3d.h"

#include <vector>
#include <string>

namespace Crystal {
	namespace Command {

class TriangleMeshGetCommand : public ICommand
{
public:
	TriangleMeshGetCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< int > meshId;
		Arg< int > layer;
	};

	struct Results : IResults
	{
		Results();

		Result< std::vector<Math::Triangle3d> > triangles;
		Result< std::vector<Math::Vector3dd>> normals;
		Result< std::string > name;
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