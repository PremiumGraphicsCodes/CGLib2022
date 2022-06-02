#include "MVPSampler.h"

#include "MVP/MVPFluidScene.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPSampler::split(const std::list<IMVPFluidScene*>& fluids)
{
	for (auto f : fluids) {
		const auto fps = f->getParticles();
		std::vector<MVPVolumeParticle*> ps;
		for (auto p : fps) {
			if (p->getDensity() < 0.75) {
				ps.push_back(p);
			}
		}
		for (auto p : ps) {
			const auto masses = p->getMassParticles();
			for (auto m : masses) {
				MVPVolumeParticle* vp = new MVPVolumeParticle(p->getRadius() * 0.50f, m->getPosition());
				vp->setVelocity(m->getVelocity());
				vp->addMassParticle(m);
				m->setParent(vp);
				vp->setRestMass(m->getMass() * 1.25f);
				f->add(vp);
			}
			p->clearMasses();
		}
	}

	for (auto f : fluids) {
		f->removeDegeneratedVolumes();
	}
}

void MVPSampler::merge(const std::list<IMVPFluidScene*>& fluids, const double searchRadius)
{
	std::list<MVPVolumeParticle*> tinyParticles;
	for (auto fluid : fluids) {
		const auto fps = fluid->getParticles();
		for (auto p : fps) {
			if (p->getMassParticles().size() == 1) {
				tinyParticles.push_back(p);
			}
		}
		CompactSpaceHash3d spaceHash(searchRadius * 0.5, static_cast<int>(tinyParticles.size()));
		for (auto p : tinyParticles) {
			spaceHash.add(p);
		}
		for (auto p : tinyParticles) {
			const auto neighbors = spaceHash.findNeighbors(p->getPosition());
			if (neighbors.size() >= 8) {
				//std::cout << "IsAbleToMerge" << std::endl;
				//auto target = static_cast<MVPVolumeParticle*>(p);
				Vector3df newPosition(0, 0, 0);
				Vector3df newVelocity(0, 0, 0);
				std::vector<MVPMassParticle*> masses;
				float r = 0.0;
				for (int i = 0; i < 8; ++i) {
					auto n = static_cast<MVPVolumeParticle*>(neighbors[i]);
					//fluid = n->
					r = n->getRadius();
					auto m = n->getMassParticles().front();
					masses.push_back(m);
					//target->addMassParticle(m);
					//m->setParent(target);
					n->clearMasses();
					newPosition += n->getPositionf();
					newVelocity += n->getVelocity();
					spaceHash.remove(n);
				}
				newPosition /= 8.0f;
				newVelocity /= 8.0f;
				MVPVolumeParticle* target = new MVPVolumeParticle(r * 2.0f, newPosition);
				target->setVelocity(newVelocity);
				for (auto m : masses) {
					target->addMassParticle(m);
					m->setParent(target);
				}
				target->setRestMass(masses[0]->getMass() * 8.0f * 1.25f);
				fluid->addParticle(target);
			}
		}
	}
	for (auto f : fluids) {
		f->removeDegeneratedVolumes();
	}

}