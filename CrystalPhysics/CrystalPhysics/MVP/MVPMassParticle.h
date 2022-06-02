#pragma once

#include "Crystal/Math/Vector3d.h"
#include "Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;

class MVPMassParticle : public Shape::IParticle
{
public:
	MVPMassParticle(MVPVolumeParticle* parent, const Math::Vector3df& point, const float mass);

	Math::Vector3dd getPosition() const override;

	Math::Vector3df getVelocity() const;

	MVPVolumeParticle* getParent() { return parent; }

	void setParent(MVPVolumeParticle* p) { this->parent = p; }

	void updatePosition(const Math::Vector3df& centerPosition);

	void updateVelocity(const Math::Vector3df& centerVelocity);

	void updateTemperature(const float t) { this->temperature = t; }

	float getMass() const { return mass; }

	void setPressureCoe(const float c) { this->pressureCoe = c; }

	float getPressureCoe() const { return this->pressureCoe; }

	void setViscosityCoe(const float v) { this->viscosityCoe = v; }

	float getViscosityCoe() const { return viscosityCoe; }

	void setHeatDiffuseCoe(const float c) { this->heatDiffuseCoe = c; }

	float getHeatDiffuseCoe() const { return heatDiffuseCoe; }

	Math::Vector3df position;

	float getTemperature() const { return temperature; }

	int lifeTime = 0;

private:
	MVPVolumeParticle* parent;
	Math::Vector3df vector;
	Math::Vector3df velocity;
	float mass;
	float pressureCoe;
	float viscosityCoe;
	float heatDiffuseCoe;
	float temperature;
};

	}
}
