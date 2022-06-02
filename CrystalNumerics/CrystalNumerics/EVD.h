#pragma once

#include "../../Crystal/Math/Vector2d.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Matrix2d.h"
#include "../../Crystal/Math/Matrix3d.h"
#include "../../Crystal/Math/Matrix4d.h"

namespace Crystal {
	namespace Numerics {

class EVD
{
public:
	struct EVD2dResult
	{
		bool isOk;
		Math::Vector2dd eigenValues;
		Math::Matrix2dd eigenVectors;
	};

	EVD2dResult calculate(const Math::Matrix2dd& lhs);

	struct EVD3dResult
	{
		bool isOk;
		Math::Vector3dd eigenValues;
		Math::Matrix3dd eigenVectors;
	};

	EVD3dResult calculate(const Math::Matrix3dd& lhs);

private:
	//std::vector<std::vector
};

	}
}