#pragma once

#include "CrystalScene/Command/ICommand.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include <vector>

namespace Crystal {
	namespace Space {

class SparseVolumeSceneCreateCommand : public Command::ICommand
{
public:
	SparseVolumeSceneCreateCommand() :
		Command::ICommand(&args, &results)
	{}

	struct Args : Command::IArgs
	{
		Args();

		Command::Arg< int > resolutionX;
		Command::Arg< int > resolutionY;
		Command::Arg< int > resolutionZ;
		Command::Arg< Math::Box3dd > boundingBox;
		Command::Arg< std::string> name;
	};

	struct Results : Command::IResults
	{
		Results();

		Command::Result<int> newId;
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