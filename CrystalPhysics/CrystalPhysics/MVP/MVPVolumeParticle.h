#pragma once

#include "MVPMassParticle.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;

class MVPVolumeParticle : public Shape::IParticle
{
public:
	MVPVolumeParticle(const float radius, const Math::Vector3dd& position);

	~MVPVolumeParticle();

	void clearMasses() { this->massParticles.clear(); }

	void setPosition(const Math::Vector3df& p) { this->position = p; }

	//void setVelocity(const Math::Vector3df& v) { this->velocity = v; }

	void setPressureCoe(const float c);

	void setViscosityCoe(const float c);

	void setVorticityCoe(const float c);

	void setHeatDiffuseCue(const float c);

	void setDragForceCoe(const float c) { this->dragForceCoe = c; }

	void setDragHeatCoe(const float c) { this->dragHeatCoe = c; }

	//KFFluidScene* getScene() { return scene; }

	void reset(bool resetMicro);

	void addNeighbor(MVPVolumeParticle* neighbor) { this->neighbors.push_back(neighbor); }

	void addMassParticle(MVPMassParticle* massParticle) { this->massParticles.push_back(massParticle); }

	void calculateDensity();

	//void calculatePressure();

	void calculatePressureForce(const float relaxationCoe, const float dt);

	void calculateViscosityForce();

	void calculateHeatDiffuse();

	void stepTime(const float dt);

	void setRadius(const float r) { this->radius = r; }

	float getRadius() const { return radius; }

	std::vector<MVPMassParticle*> getPoints() { return massParticles; }

	Math::Vector3dd getPosition() const override { return position; }

	Math::Vector3df getPositionf() const { return position; }

	Math::Vector3df getVelocity() const { return velocity; }

	void addForce(const Math::Vector3dd& force) { this->force += force; }

	float getDensity() const;

	void updateMassPositions();

	void updateMassVelocities();

	void updateMassTemperatures();

	void updateInnerPoints();

	float getSelfMass() { return restMass; }

	void setVelocity(const Math::Vector3df& velocity) { this->velocity = velocity; }

	void setRestMass(const float m) { this->restMass = m; }

	Math::Vector3df getAveragedCenter() const { return averagedCenter; }

	const std::vector<MVPMassParticle*>& getMassParticles() const { return massParticles; }

	const std::vector<MVPVolumeParticle*>& getNeighbors() const { return neighbors; }

	void setTemperature(const float t) { this->temperature = t; }

	float getTemperature() const { return this->temperature; }

	void calculateDragForce();

	void calculateDragHeat();

private:
	float pressureCoe;
	float viscosityCoe;
	float radius;
	//float vorticityCoe;
	std::vector<MVPMassParticle*> massParticles;
	std::vector<MVPMassParticle*> innerPoints;
	std::vector<MVPVolumeParticle*> neighbors;
	Math::Vector3df force;
	Math::Vector3df position;
	Math::Vector3df predictedPosition;
	Math::Vector3df velocity;
	Math::Vector3df averagedCenter;
	float temperature;
	float enthaply;
	float restMass;
	float density;
	float pressure;
	float dragForceCoe = 0.0f;
	float dragHeatCoe = 0.0f;
};

	}
}