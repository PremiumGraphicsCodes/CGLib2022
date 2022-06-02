#pragma once

#include "Vector3d.h"
#include "IVolume3d.h"

#include <vector>

namespace Crystal {
	namespace Math {

class Space3d
{
public:
	void add(IVolume3dd* volume);

	bool isInside(const Math::Vector3dd& position) const;

private:
	std::vector<IVolume3dd*> volumes;
};

	}
}

