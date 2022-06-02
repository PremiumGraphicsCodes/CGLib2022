#pragma once

#include <list>
#include <vector>
#include <memory>

#include "../../../Crystal/Math/Vector3d.h"
#include "../../../Crystal/Shape/IParticle.h"

#include "../SPHKernel.h"
#include "../SPHConstant.h"

namespace Crystal {
	namespace Physics {
		class PBFluidScene;
		class PBSPHParticle;

class PBSPHBoundaryParticle : public Shape::IParticle
{
public:
	PBSPHBoundaryParticle(const Math::Vector3df& center, const float radius, PBFluidScene* scene);

	virtual ~PBSPHBoundaryParticle() {};

	float getDensityRatio() const;

	float getMass() const;

	float getVolume() const;

	float getRestVolume() const;

	void setDefaultDensity();

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	void init();

	//void solveViscosity(const float distance);

	//float getEffectLength() const;

	Math::Vector3dd getPosition() const { return position; }

	void calculatePressure(const PBSPHParticle& rhs);

	void calculateViscosity(const PBSPHParticle& rhs);

	void setDensity(const float d) { this->density = d; }

	double getRadius() const { return radius; }

private:
	Math::Vector3df position;
	float radius;
	float density;

	PBFluidScene* scene;

	//SPHKernel* getKernel();
};

	}
}
