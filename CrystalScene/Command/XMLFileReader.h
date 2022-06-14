#pragma once

#include <filesystem>
#include <map>
#include "tinyxml2.h"
#include "PropertyTree.h"
#include "IPropertyTreeFactory.h"

namespace Crystal {
	namespace Command {

class XMLFileReader
{
public:
	bool read(const std::filesystem::path& path);

	std::unique_ptr<PropertyTree> getTree() { return std::move(tree); }

private:
	std::unique_ptr<PropertyTree> tree;
	//std::map<std::string, typeid>

	bool read(tinyxml2::XMLElement* parent, PropertyTree& t);

};

	}
}