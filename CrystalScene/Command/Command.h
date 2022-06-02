#pragma once

#include <string>
#include <memory>
#include <any>

#include "ICommand.h"

namespace Crystal {
	namespace Scene {
		class World;
	}
	namespace Command {

class Command
{
public:
	Command() {}

	explicit Command(const std::string& name);

	~Command();

	void create(const std::string& name);

	void clear();

	void setArg(const std::string& name, std::any value);

	const std::type_info& getArgType(const std::string& name);

	bool execute(Scene::World* scene);

	std::any getResult(const std::string& name);

	//void saveJSON(const std::string& filePath);

private:
	std::unique_ptr<ICommand> command;
};
	}
}