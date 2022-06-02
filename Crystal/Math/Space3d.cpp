#include "Space3d.h"

using namespace Crystal::Math;

void Space3d::add(IVolume3dd* volume)
{
	this->volumes.push_back(volume);
}

bool Space3d::isInside(const Vector3dd& position) const
{
	for (auto v : volumes) {
		if (!v->isInside(position)) {
			return false;
		}
	}
	return true;
}
