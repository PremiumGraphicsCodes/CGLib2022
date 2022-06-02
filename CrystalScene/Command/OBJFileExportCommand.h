#pragma once

#include "ICommand.h"
#include <filesystem>
#include "../Scene/PolygonMeshScene.h"

namespace Crystal {
	namespace Command {

class OBJFileExportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< std::vector<int> > ids;
		Arg< std::string > filePath;
	};

	struct Results : IResults
	{
		Results();

		//Result< bool > isOk;
	};

	OBJFileExportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	bool exportOBJ(const std::filesystem::path& filePath, const std::vector<Scene::PolygonMeshScene*>& polygons);

	bool exportMTL(const std::filesystem::path& filePath, Scene::PolygonMeshScene& appearances);

private:
	Args args;
	Results results;
};

	}
}