#pragma once

#include "Crystal/Math/Vector3d.h"
#include <vector>

namespace Crystal {
	namespace Renderer {

class GLCube
{
public:
	GLCube();

	GLCube(const Math::Vector3df& min, const Math::Vector3df& max);

	std::vector<Math::Vector3df> toGLArray() const;

private:
	Math::Vector3df min;
	Math::Vector3df max;
};
	}
}