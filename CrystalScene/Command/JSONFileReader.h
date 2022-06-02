#pragma once

#include <filesystem>
#include "ICommand.h"
#include "CommandFactory.h"

namespace Crystal {
	namespace Command {

class JSONFileReader
{
public:
	bool read(const std::filesystem::path& path, const ICommandFactory& factory);

	std::vector<std::unique_ptr<ICommand>> getCommands() { return std::move(commands); }

private:
	std::vector<std::unique_ptr<ICommand>> commands;
};

	}
}