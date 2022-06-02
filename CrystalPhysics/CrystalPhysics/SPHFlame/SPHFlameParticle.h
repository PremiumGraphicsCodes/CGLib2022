#pragma once

#include "../CSPH/CSPHParticle.h"

namespace Crystal {
	namespace Physics {

struct SPHFlameConstant
{
	float k_hd;
	float k_fd;
	float k_rs;
	float k_buo;
};

class SPHFlameParticle : public CSPHParticle
{
public:
	SPHFlameParticle(const Math::Vector3df& center, const float radius, SPHConstant* constant, SPHFlameConstant* flameConstant);

	void init() override;

	void forwardTime(const float dt) override;

	void solveHeatDiffuse(const SPHFlameParticle& rhs);

	void solveFuelDiffuse(const SPHFlameParticle& rhs);

	float getReactionSpeed();

	Math::Vector3df getBuoyancyForce();

	void setFuel(const float fuel) { this->fuel = fuel; }

	float getFuel() const { return this->fuel; }

	void setTemperature(const float t) { this->temperature = t; }

	float getTemperature() const { return this->temperature; }

	void setStatic(const bool b) { this->isStatic = b; }

	bool isFire() const;

private:
	float temperature;
	float fuel;
	float enthalpy;
	float dfuel;
	SPHFlameConstant* flameConstant;
	bool isStatic;
};

	}
}