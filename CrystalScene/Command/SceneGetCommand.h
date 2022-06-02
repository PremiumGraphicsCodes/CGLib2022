#pragma once

#include "ICommand.h"
#include "../Scene/Scene.h"

namespace Crystal {
	namespace Command {

class SceneGetCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<int> id;
	};

	struct Results : IResults
	{
		Results();

		//Result<Math::Vector3dd> center;
		Result<bool> isVisible;
		Result<bool> isPickable;
		Result<std::string> name;
		Result<Math::Box3dd> boundingBox;
		Result<std::string> typeName;
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	SceneGetCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}