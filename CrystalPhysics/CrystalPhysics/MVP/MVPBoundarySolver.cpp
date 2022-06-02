#include "MVPBoundarySolver.h"

#include "MVPVolumeParticle.h"
#include "MVPFluidScene.h"
#include "../Boundary/CSGBoundaryScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPBoundarySolver::setup(const float effectLength)
{
	std::vector<MVPVolumeParticle*> boundaryParticles;
	for (auto b : boundaries) {
		const auto bp = b->getParticles();
		boundaryParticles.insert(boundaryParticles.end(), bp.begin(), bp.end());
	}

	if (boundaryParticles.empty()) {
		return;
	}

	const auto hashSize = boundaryParticles.front()->getPoints().size() * boundaryParticles.size();
	const auto searchRadius = effectLength;
	spaceHash = std::make_unique<CompactSpaceHash3d>(searchRadius, static_cast<int>(boundaryParticles.size()));
	//spaceHash.setup(searchRadius, boundaryParticles.size());

	for (auto bp : boundaryParticles) {
		spaceHash->add(bp);
		/*
		const auto& microParticles = bp->getPoints();
		for (auto mp : microParticles) {
			spaceHash->add(mp);
		}
		*/
	}
}

std::vector<IParticle*> MVPBoundarySolver::findNeighbors(const Vector3dd& position)
{
	if (spaceHash == nullptr) {
		return {};
	}
	return spaceHash->findNeighbors(position);
}

MVPVolumeParticle* MVPBoundarySolver::createGphost(const Vector3df& p, MVPVolumeParticle* particle)
{
	const auto radius = particle->getRadius();
	auto massP = particle->getMassParticles().front();
	const auto mass = massP->getMass();

	auto vp = new MVPVolumeParticle(radius, p);
	if (particle->getMassParticles().size() == 1) {
		MVPMassParticle* mp = new MVPMassParticle(vp, Vector3df(0, 0, 0), mass);
		mp->setParent(vp);
		vp->addMassParticle(mp);
	}
	else {
		const auto e = 1.0e-12;
		for (float x = -radius; x < radius + e; x += radius * 2.0f) {
			for (float y = -radius; y < radius + e; y += radius * 2.0f) {
				for (float z = -radius; z < radius + e; z += radius * 2.0f) {
					MVPMassParticle* mp = new MVPMassParticle(vp, Vector3df(x, y, z), mass * 8.0f);
					mp->setParent(vp);
					vp->addMassParticle(mp);
				}
			}
		}
	}
	vp->setPressureCoe(massP->getPressureCoe());
	vp->setViscosityCoe(massP->getViscosityCoe());

	return vp;
}

void MVPBoundarySolver::createGphosts(MVPVolumeParticle* particle)
{
	const auto r = particle->getRadius();
	for (const auto& csg : csgBoundaries) {
		for (const auto& boundary : csg->getBoxes()) {
			auto position = particle->getPosition();
			if (position.y < boundary.getMinY() - r) {
				position.y = boundary.getMinY() - r;
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
			if (position.y > boundary.getMaxY() + r) {
				const auto distance = boundary.getMinY() + r;
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
			if (position.x > boundary.getMaxX() + r) {
				const auto distance = boundary.getMinX() + r;
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
			if (position.x < boundary.getMinX() - r) {
				const auto distance = boundary.getMinX() - r;
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
			if (position.z > boundary.getMaxZ() + r) {
				const auto distance = boundary.getMaxZ() + r;
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
			if (position.z < boundary.getMinZ() - r) {
				const auto distance = boundary.getMinZ() - r;
				const auto overlap = Vector3dd(0, 0, distance);
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
		}
	}
}

void MVPBoundarySolver::clearGphosts()
{
	for (auto g : ghosts) {
		delete g;
	}
	ghosts.clear();
}

void MVPBoundarySolver::solvePressure(MVPVolumeParticle* particle, const double dt)
{
	for (const auto& csg : csgBoundaries) {
		for (const auto& boundary : csg->getBoxes()) {
			auto position = particle->getPosition();
			if (position.y < boundary.getMinY()) {
				const auto distance = boundary.getMinY() - position.y;
				const auto overlap = Vector3dd(0, distance, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.y > boundary.getMaxY()) {
				const auto distance = boundary.getMaxY() - position.y;
				const auto overlap = Vector3dd(0, distance, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.x > boundary.getMaxX()) {
				const auto distance = boundary.getMaxX() - position.x;
				const auto overlap = Vector3dd(distance, 0, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.x < boundary.getMinX()) {
				const auto distance = boundary.getMinX() - position.x;
				const auto overlap = Vector3dd(distance, 0, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.z > boundary.getMaxZ()) {
				const auto distance = boundary.getMaxZ() - position.z;
				const auto overlap = Vector3dd(0, 0, distance);
				particle->addForce(overlap / dt / dt);
			}
			if (position.z < boundary.getMinZ()) {
				const auto distance = boundary.getMinZ() - position.z;
				const auto overlap = Vector3dd(0, 0, distance);
				particle->addForce(overlap / dt / dt);
			}
		}
	}

}
