#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include <vector>
#include <string>

namespace Crystal {
	namespace Command {

class ParticleSystemGetCommand : public ICommand
{
public:
	ParticleSystemGetCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< int > psId;
		Arg< int > layer;
	};

	struct Results : IResults
	{
		Results();

		Result< std::vector<Math::Vector3dd> > positions;
		Result< float > pointSize;
		Result< Graphics::ColorRGBAf > color;
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