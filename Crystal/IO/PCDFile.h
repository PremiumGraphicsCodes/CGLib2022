#pragma once

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

struct PCDFile
{
	struct Header
	{
		int width = 0;
		int points = 0;
		bool isBinary = false;
	};
	struct Data
	{
		std::vector<Math::Vector3dd> positions;
	};
	Header header;
	Data data;
};

	}
}