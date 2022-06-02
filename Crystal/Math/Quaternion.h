#ifndef __CRYSTAL_MATH_QUATERNION_H__
#define __CRYSTAL_MATH_QUATERNION_H__

#include "glm.h"
#include "../ThirdParty/glm-0.9.9.3/glm/gtc/quaternion.hpp"
//#include "../ThirdParty/glm-0.9.9.3/glm/gtx/quaternion.hpp"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

using Quaternion = glm::quat;

// from http://www.opengl-tutorial.org/jp/intermediate-tutorials/tutorial-17-quaternions/
static glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest) {
	start = normalize(start);
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f) {
		// ベクトルが反対方向を向いている特殊なケース：
		// 単位回転軸はないので、垂直なものを見つけます。
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (getLengthSquared(rotationAxis) < 0.01) { // 残念、平行なのでもう一度！
			rotationAxis = cross(glm::vec3(1.0f, 0.0f, 0.0f), start);
		}

		rotationAxis = normalize(rotationAxis);
		return glm::angleAxis(glm::radians(180.0f), rotationAxis);
	}

	rotationAxis = cross(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

}

	}
}

#endif