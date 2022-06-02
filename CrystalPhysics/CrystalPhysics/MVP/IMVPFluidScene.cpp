#include "IMVPFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

IMVPFluidScene::IMVPFluidScene(const int id, const std::string& name) :
	IParticleSystemScene(id, name),
	pressureCoe(10000.0),
	viscosityCoe(50.0)
{
	this->controller = std::make_unique<MVPFluidScenePresenter>(this);
}

IMVPFluidScene::~IMVPFluidScene()
{
	clearParticles();
}

void IMVPFluidScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3dd IMVPFluidScene::getBoundingBox() const
{
	if (particles.empty()) {
		return Box3dd::createDegeneratedBox();
	}
	Box3d bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}

std::vector<Vector3dd> IMVPFluidScene::getPositions() const
{
	std::vector<Vector3dd> positions;
	for (auto p : particles) {
		positions.push_back(p->getPosition());
	}
	return positions;
}
#include <algorithm>
#include <iterator>

void IMVPFluidScene::removeDegeneratedVolumes()
{
	this->particles.sort();
	std::list<MVPVolumeParticle*> vps;
	for (auto v : particles) {
		if (v->getMassParticles().empty()) {
			vps.push_back(v);
		}
	}
	std::list<MVPVolumeParticle*> diffs;
	std::set_difference(
		this->particles.begin(), this->particles.end(),
		vps.begin(), vps.end(),
		std::inserter(diffs, diffs.end())
	);
	this->particles = diffs;
	for (auto v : vps) {
		delete v;
	}
	removeExpired();
}

void IMVPFluidScene::removeExpired()
{
	std::list<MVPVolumeParticle*> vps;
	if (lifeLimit != -1) {
		for (auto v : particles) {
			if (v->getMassParticles().front()->lifeTime > lifeLimit) {
				v->clearMasses();
				vps.push_back(v);
			}
		}
	}
	std::list<MVPVolumeParticle*> diffs;
	std::set_difference(
		this->particles.begin(), this->particles.end(),
		vps.begin(), vps.end(),
		std::inserter(diffs, diffs.end())
	);
	this->particles = diffs;
	for (auto v : vps) {
		delete v;
	}
}

MVPVolumeParticle* IMVPFluidScene::create(const Vector3df& position, const float radius, const float weight, const float temperature)
{
	auto vp = new MVPVolumeParticle(radius, position);
	auto mp = new MVPMassParticle(vp, Vector3dd(0, 0, 0), weight);
	mp->updateTemperature(1000.0f);
	vp->setRestMass(weight * 1.25f);
	vp->addMassParticle(mp);
	vp->setTemperature(temperature);
	mp->setParent(vp);

	//vp->addMassParticle(mp);
	return vp;
	//	restMass *= 1.5;
	//	selfMass = unum * vnum * wnum * weight;
}
