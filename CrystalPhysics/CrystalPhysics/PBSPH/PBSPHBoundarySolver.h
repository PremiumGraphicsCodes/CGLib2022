#pragma once

#include "../../../Crystal/Math/Vector3d.h"
#include "../../../Crystal/Math/Box3d.h"
#include "../../../CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"

namespace Crystal {
	namespace Physics {
		class PBSPHParticle;
		class PBSPHBoundaryParticle;

class PBSPHBoundarySolver
{
public:
	PBSPHBoundarySolver() {};

	PBSPHBoundarySolver(const Math::Box3dd& boundary);

	void addDX(const std::vector<PBSPHParticle*>& particles, const float dt);

	void calculatePressure(const std::vector<PBSPHParticle*>& particles);

	void calculateViscosity(const std::vector<PBSPHParticle*>& particles);

private:
	bool isBoundary(PBSPHParticle* particle);

	Math::Vector3df getBoundaryPosition(PBSPHParticle* particle);

	Math::Vector3df getOverVector(const Math::Vector3df& position);

	float getOverX(const float x);
	float getOverY(const float y);
	float getOverZ(const float z);

	const Math::Box3dd boundary;

};

class PBSPHBoundarySolver2
{
public:
	PBSPHBoundarySolver2(const double searchRadius, const int tableSize);

	void searchNeighbors(const std::vector<PBSPHParticle*>& particles);

	void calculateDensity(const std::vector<PBSPHParticle*>& particles);

	//void calculatePressure(const std::vector<PBSPHParticle*>& particles);

private:
	std::vector<PBSPHBoundaryParticle*> boundaryParticles;
	Space::CompactSpaceHash3d spaceHash;

};
	}
}
