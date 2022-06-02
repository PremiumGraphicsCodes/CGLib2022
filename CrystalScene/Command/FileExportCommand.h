#pragma once

#include "IArgs.h"
#include "ICommand.h"
#include <vector>

#include "../../Crystal/IO/FileFormat.h"

namespace Crystal {
	namespace Command {

class FileExportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< std::string > filePath;
	};

	struct Results : IResults
	{
		Results();
	};

	FileExportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	bool exportFile(const std::filesystem::path& filePath, const IO::FileFormat format, Scene::World* world);

private:
	Args args;
	Results results;
};

	}
}