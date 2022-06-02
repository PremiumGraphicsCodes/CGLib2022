#include "JSONFileWriter.h"
#include "JSONConverter.h"
#include <fstream>

using namespace Crystal::Command;

void JSONFileWriter::add(ICommand* command)
{
	commands.push_back(command);
}

bool JSONFileWriter::write(const std::filesystem::path& path)
{
	std::ofstream stream(path);
	if (!stream.is_open()) {
		return false;
	}
	JSONConverter converter;
	nlohmann::json root;
	for (auto c : commands) {
		const auto name = c->getCommandName();
		const auto j = converter.toJSON(*c->getArgs());
		root.push_back({ name, j });
	}
	stream << std::setw(4) << root << std::endl;
	return true;
}
