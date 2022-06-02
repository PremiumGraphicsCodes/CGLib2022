#pragma once

#include <filesystem>
#include "ICommand.h"

namespace Crystal {
	namespace Command {

class JSONFileWriter
{
public:
	void add(ICommand* command);

	bool write(const std::filesystem::path& path);

private:
	std::vector<ICommand*> commands;
};
	}
}