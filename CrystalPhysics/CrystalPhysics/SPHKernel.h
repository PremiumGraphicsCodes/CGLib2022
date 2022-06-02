#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Matrix3d.h"

namespace Crystal {
	namespace Physics {

class SPHKernel
{
public:
	SPHKernel() = default;

	SPHKernel(const float effectLength);

	float getPoly6Kernel(const float distance);

	float getPoly6Kernel2(const float distanceSquared);

	//float getPoly6Kernel(const float distance, const float effectLength);

	Math::Vector3df getPoly6KernelGradient(const Math::Vector3df& distanceVector);

	float getPoly6KernelGradientCoe(const float distance);

	float getPoly6KernelLaplacian(const float distance);

	Math::Vector3df getSpikyKernelGradient(const Math::Vector3df& distanceVector) const;

	float getSpikyKernelGradientWeight(const float distance);

	//Math::Vector3df getSpikyKernelGradient(const Math::Vector3df& distanceVector);

	float getViscosityKernelLaplacian(const float distance);

	//float getCubicSpline(const float q);

	float getCubicSpline(const float distance) const;

	float getCubicSpline(const Math::Vector3df& v) const;

	Math::Vector3df getCubicSplineGradient(const Math::Vector3df& distanceVector);

	float getEffectLength() const { return effectLength; }

	//void setEffectLength(const float el) { this->effectLength = el; }

private:
	float effectLength;
	float poly6KernelConstant;
	float spikyKernelGradConstant;
	float effectLengthSquared;
};

	}
}
