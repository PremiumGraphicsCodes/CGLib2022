#include "ICommand.h"

#include "JSONConverter.h"
#include <fstream>

using namespace Crystal::Command;

/*
void ICommand::writeJSON(const std::string& filePath)
{
	auto j = JSONConverter::toJSON(*this);
	std::ofstream stream(filePath);
	stream << j;
}

void ICommand::readJSON(const std::string& filePath)
{
	std::ifstream stream(filePath);
	nlohmann::json j;
	stream >> j;
	JSONConverter::fromJSON(j, *this);
}
*/