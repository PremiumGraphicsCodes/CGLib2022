#pragma once

#include <vector>
#include "Crystal/Math/Vector3d.h"
#include "Crystal/Math/Box2d.h"
#include "Crystal/Math/Sphere3d.h"

namespace Crystal {
	namespace Renderer {

class GLPolygonBuilder
{
public:

	void add(const Math::Sphere3df& sphere, const int unum, const int vnum);

private:
	std::vector<Math::Vector3df> positions;
	std::vector<Math::Vector3df> normals;
	std::vector<unsigned int> indices;
};
	}
}