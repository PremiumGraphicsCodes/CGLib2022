#pragma once

#include "ICommand.h"
#include <filesystem>

namespace Crystal {
	namespace Command {

class PLYFileImportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< std::string > filePath;
		Arg< int > particleSystemId;
	};

	struct Results : IResults
	{
		Results();
	};

	PLYFileImportCommand() :
		ICommand(&args, &results)
	{}

	explicit PLYFileImportCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}