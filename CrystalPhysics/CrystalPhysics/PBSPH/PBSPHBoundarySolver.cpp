#include "PBSPHBoundarySolver.h"

#include "PBSPHParticle.h"
#include "../SPHKernel.h"

#include "PBSPHBoundaryParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

namespace {
	SPHKernel kernel;
}

PBSPHBoundarySolver::PBSPHBoundarySolver(const Box3dd& boundary) :
	boundary(boundary)
{
}

void PBSPHBoundarySolver::addDX(const std::vector<PBSPHParticle*>& particles, const float dt)
{
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto over = getOverVector(particles[i]->getPredictPosition());
		particles[i]->addDensity(glm::length(over), particles[i]->getMass());
		//particles[i]->calculatePressure(-over);
		//particles[i]->dx -= over * 0.1f;
		//particles[i]->addExternalForce(-over / dt / dt);
	}
}

void PBSPHBoundarySolver::calculatePressure(const std::vector<PBSPHParticle*>& particles)
{
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto over = getOverVector(particles[i]->getPredictPosition());
		//particles[i]->calculatePressure(over);
		particles[i]->dx -= over * 0.1f;
		//particles[i]->addExternalForce(-over / dt / dt);
	}
}

void PBSPHBoundarySolver::calculateViscosity(const std::vector<PBSPHParticle*>& particles)
{
	/*
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto over = getOverVector(particles[i]->getPredictPosition());
		//particles[i]->calculatePressure(over);
		const auto coe = glm::length(over) * 1.0f;
		particles[i]->xvisc = coe * -particles[i]->getVelocity();
		//particles[i]->addExternalForce(-over / dt / dt);
	}
	*/
}



bool PBSPHBoundarySolver::isBoundary(PBSPHParticle* particle)
{
	const auto& pos = particle->getPosition();
	const auto radii = particle->getEffectLength();
	if (pos.x + radii > boundary.getMaxX()) {
		return true;
	}
	if (pos.y + radii > boundary.getMaxY()) {
		return true;
	}
	if (pos.z + radii > boundary.getMaxZ()) {
		return true;
	}
	if (pos.x - radii < boundary.getMinX()) {
		return true;
	}
	if (pos.y - radii < boundary.getMinY()) {
		return true;
	}
	if (pos.z - radii < boundary.getMinZ()) {
		return true;
	}
	return false;
}

Vector3df PBSPHBoundarySolver::getBoundaryPosition(PBSPHParticle* particle)
{
	assert(isBoundary(particle));
	const auto& pos = particle->getPosition();
	const auto radii = particle->getEffectLength();
	if (pos.x + radii > boundary.getMaxX()) {
		return Vector3df(boundary.getMaxX() + radii, pos.y, pos.z);
	}
	if (pos.y + radii > boundary.getMaxY()) {
		return Vector3df(pos.x, boundary.getMaxY() + radii, pos.z);
	}
	if (pos.z + radii > boundary.getMaxZ()) {
		return Vector3df(pos.x, pos.y, boundary.getMaxZ() + radii);
	}
	if (pos.x - radii < boundary.getMinX()) {
		return Vector3df(boundary.getMinX() - radii, pos.y, pos.z);
	}
	if (pos.y - radii < boundary.getMinY()) {
		return Vector3df(pos.x, boundary.getMinY() - radii, pos.z);
	}
	if (pos.z - radii < boundary.getMinZ()) {
		return Vector3df(pos.x, pos.y, boundary.getMinZ() - radii);
	}
	assert(false);
	return Vector3df(0, 0, 0);
}


Vector3df PBSPHBoundarySolver::getOverVector(const Vector3df& position)
{
	return Vector3df(getOverX(position.x), getOverY(position.y), getOverZ(position.z));
}

float PBSPHBoundarySolver::getOverX(const float x)
{
	float over = 0;
	if (x > boundary.getMaxX()) {
		over = x - static_cast<float>(boundary.getMaxX());
	}
	else if (x < boundary.getMinX()) {
		over = x - static_cast<float>(boundary.getMinX());
	}
	return over;
}

float PBSPHBoundarySolver::getOverY(const float y)
{
	float over = 0;
	if (y > boundary.getMaxY()) {
		over = y - static_cast<float>(boundary.getMaxY());
	}
	else if (y < boundary.getMinY()) {
		over = y - static_cast<float>(boundary.getMinY());
	}
	return over;
}

float PBSPHBoundarySolver::getOverZ(const float z)
{
	float over = 0;
	if (z > boundary.getMaxZ()) {
		over = z - static_cast<float>(boundary.getMaxZ());
	}
	else if (z < boundary.getMinZ()) {
		over = z - static_cast<float>(boundary.getMinZ());
	}
	return over;
}

PBSPHBoundarySolver2::PBSPHBoundarySolver2(const double searchRadius, const int tableSize) :
	spaceHash(searchRadius, tableSize)
{}

void PBSPHBoundarySolver2::searchNeighbors(const std::vector<PBSPHParticle*>& particles)
{
	spaceHash.clear();
	for (auto p : particles) {
		spaceHash.add(p);
	}
}

void PBSPHBoundarySolver2::calculateDensity(const std::vector<PBSPHParticle*>& particles)
{
	for (auto bp : boundaryParticles) {
		// 一番近い粒子の密度をコピーする．
		const auto neighbors = spaceHash.findNeighbors(bp->getPosition());
		auto closest = *neighbors.begin();
		double minDistance2 = std::numeric_limits<double>().max();
		for (auto n : neighbors) {
			const auto d2 = Math::getDistanceSquared(n->getPosition(), bp->getPosition());
			if (d2 < minDistance2) {
				closest = n;
			}
		}
		/*
		auto closest = std::min_element(neighbors.begin(), neighbors.end(), [bp](PBSPHParticle* p) {
			return Math::getDistanceSquared(bp->getPosition(), p->getPosition());
		});
		*/
	}
}
