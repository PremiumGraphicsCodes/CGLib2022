#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include <vector>
#include <string>

namespace Crystal {
	namespace Command {

class ParticleSystemSetCommand : public ICommand
{
public:
	ParticleSystemSetCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< int > psId;
		Arg< std::vector<Math::Vector3dd> > positions;
		Arg< float > pointSize;
		Arg< Graphics::ColorRGBAf > color;
		Arg< std::string > name;
	};

	struct Results : IResults
	{
		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}