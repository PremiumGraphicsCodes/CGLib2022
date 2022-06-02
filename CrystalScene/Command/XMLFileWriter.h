#pragma once

#include <filesystem>
#include "PropertyTree.h"

namespace Crystal {
	namespace Command {

class XMLFileWriter
{
public:
	bool write(const PropertyTree& tree, const std::filesystem::path& path);

private:
};

	}
}