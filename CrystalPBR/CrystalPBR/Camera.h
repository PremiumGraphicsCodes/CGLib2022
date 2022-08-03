#pragma once

#include "Crystal/Math/Vector3d.h"
#include "Crystal/Math/Matrix3d.h"
#include "Crystal/Math/Matrix4d.h"


namespace Crystal {
	namespace Renderer {

class Camera
{
public:
	Camera();

	Math::Matrix4df getModelMatrix() const;

	Math::Matrix4df getViewMatrix() const;

	Math::Matrix4df getProjectionMatrix() const;

private:
};

	}
}