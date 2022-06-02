#pragma once

#include "../../../Crystal/Shape/IParticle.h"
#include "../SPHKernel.h"
#include <vector>

namespace Crystal {
	namespace Physics {
		class SPHConstant;

class DFSPHParticle : public Shape::IParticle
{
public:
	DFSPHParticle(const Math::Vector3df& position, const float radius, SPHConstant* constant, SPHKernel* kernel) :
		position(position),
		velocity(0,0,0),
		radius(radius),
		constant(constant),
		kernel(kernel),
		density(0.0),
		alpha(0.0)
	{}

	Math::Vector3dd getPosition() const override { return position; }

	Math::Vector3df getVelocity() const { return velocity; }

	float getRadius() const { return radius; }

	void addNeighbor(DFSPHParticle* neighbor) { this->neighbors.push_back( neighbor ); }

	void clearNeighbors() { this->neighbors.clear(); }

	std::vector<DFSPHParticle*> getNeighbors() const { return neighbors; }

	float getMass() const;

	void calculateDensity();

	void calculateAlpha();

	void calculateDpDt();

	void predictDensity(const float dt);

	void calculateVelocityInDivergenceError(const float dt);

	void calculateVelocityInDensityError(const float dt);

	void setKernel(SPHKernel* kernel) { this->kernel = kernel; }

	float getDensity() const { return density; }

	float getPredictedDensity() const { return predictedDensity; }

	float getDpDt() const { return dpdt; }

	void calculateViscosity();

	Math::Vector3df force;
	Math::Vector3df velocity;
	Math::Vector3df position;

private:
	const float radius;
	float alpha;
	float dpdt;
	float predictedDensity;
	float density;
	std::vector<DFSPHParticle*> neighbors;
	SPHKernel* kernel;
	SPHConstant* constant;

};
	}
}