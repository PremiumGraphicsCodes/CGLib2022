#include "JSONFileReader.h"
#include "JSONConverter.h"
#include <fstream>

using namespace Crystal::Command;

bool JSONFileReader::read(const std::filesystem::path& path, const ICommandFactory& factory)
{
	std::ifstream stream(path);
	if (!stream.is_open()) {
		return false;
	}
	//JSONConverter converter;
	nlohmann::json root;
	stream >> root;
	for (const auto& j : root) {
		const auto name = j[0].get<std::string>();
		auto c = factory.createCommand(name);
		JSONConverter::fromJSON(j[1], *c);
		commands.push_back(std::move(c));
	}
	/*
	for (auto c : commands) {
		const auto name = c->getCommandName();
		const auto j = converter.toJSON(*c->getArgs());
		root.push_back({ name, j });
	}
	stream << std::setw(4) << root << std::endl;
	*/
	return true;

}

//std::vector<ICommand*> getCommands() const { return commands; }
