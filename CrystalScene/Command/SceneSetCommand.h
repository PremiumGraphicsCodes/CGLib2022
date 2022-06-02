#pragma once

#include <string>
#include <any>
#include "ICommand.h"
#include "../Scene/World.h"

namespace Crystal {
	namespace Command {

class SceneSetCommand : public ICommand
{
public:
	SceneSetCommand();

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	struct Args : public IArgs
	{
		Args();

		Arg<int> id;
		Arg<std::string> name;
	};

	struct Results : public IResults
	{

	};

	bool execute(Scene::World* world);

private:
	Args args;
	Results results;
};

	}
}