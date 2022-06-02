#pragma once

#include "IArgs.h"
#include "ICommand.h"
#include <filesystem>
#include <vector>

#include "../Scene/Scene.h"
#include "../../Crystal/IO/FileFormat.h"

namespace Crystal {
	namespace Command {

class FileImportCommand : public ICommand
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

		Result< int > newId;
	};

	FileImportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	bool importFile(const std::filesystem::path& filePath, Scene::World* world);

	bool importFile(const std::filesystem::path& filePath, Scene::World* world, const IO::FileFormat format);

public:
	Args args;
	Results results;
};

	}
}