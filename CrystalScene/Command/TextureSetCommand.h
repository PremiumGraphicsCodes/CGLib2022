#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class TextureSetCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<int> id;
		Arg<std::string> filePath;
	};

	struct Results : IResults
	{
		Results();

		Result<bool> isOk;
	};

	TextureSetCommand() :
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