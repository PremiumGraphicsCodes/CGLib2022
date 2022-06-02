#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class TextureCreateCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<std::string> filePath;
		Arg<std::string> name;
	};

	struct Results : IResults
	{
		Results();

		Result<int> newId;
	};

	TextureCreateCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}