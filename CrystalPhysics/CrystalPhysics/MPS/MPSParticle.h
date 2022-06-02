#pragma once

#include "Crystal/Math/Vector3d.h"
#include "Crystal/Shape/IParticle.h"
#include <list>

namespace Crystal {
	namespace Physics {

class MPSParticle : public Shape::IParticle
{
public:
	explicit MPSParticle(const Math::Vector3df& position);

	Math::Vector3dd getPosition() const override { return position; }

	Math::Vector3df getPositionf() const { return position; }

	Math::Vector3df getVelocity() const { return velocity; }

	float getPressure() const { return pressure; }

	float getN0() const { return n0; }

	float getLamda0() const { return lamda0; }

	void forwardTime(const float timeStep);

	void addNeighbor(MPSParticle* neighbor) { this->neighbors.push_back(neighbor); }

	void addExternalForce(const Math::Vector3df& externalForce) { this->force += externalForce; }

	void calculateNumberDensity(const float maxRadius);

	void calculatePressureGradient(const float maxRadius);

	void calculateViscosity(const float maxRadius);

	void calculateN0(const float maxRadius);

	void calculateLamda0(const float maxRadius);

	float getNumberDensity() { return numberDensity; }

	void setPressure(const float p) { this->pressure = p; }

	void setN0(const float n0) { this->n0 = n0; }

	Math::Vector3df getForce() const { return force; }

private:
	float calculateNumberDensity(const MPSParticle* rhs, const float maxRadius);

	Math::Vector3df calculatePressureGradient(const MPSParticle* rhs, const float maxRadius);

	Math::Vector3df calculateViscosity(const MPSParticle* rhs, const float maxRadius);

	float calculateWeight(const float r, const float maxRadius);

private:
	float pressure;
	float n0;
	float lamda0;
	//const float radius;
	float numberDensity;
	Math::Vector3df force;
	Math::Vector3df acc;
	Math::Vector3df position;
	Math::Vector3df velocity;
	std::list<MPSParticle*> neighbors;
};

	}
}