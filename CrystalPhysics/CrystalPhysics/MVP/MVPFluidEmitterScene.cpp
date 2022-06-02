#include "MVPFluidEmitterScene.h"

#include "MVPVolumeParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

MVPFluidEmitterScene::MVPFluidEmitterScene(const int id, const std::string& name) :
	IMVPFluidScene(id, name),
	interval(10),
	initialTemperature(300.0f)
{
}

MVPFluidEmitterScene::~MVPFluidEmitterScene()
{
	clearParticles();
}

void MVPFluidEmitterScene::emitParticle(const int timeStep)
{
	const auto start = getStartStep();
	const auto end = getEndStep();
	if (start <= timeStep && timeStep <= end) {
		const auto elapsed = timeStep - start;
		if (elapsed % interval == 0) {
			for (const auto& s : sourcePositions) {
				auto mp = create(s.getCenter(), s.getRadius(), 0.25f, initialTemperature);
				mp->setTemperature(initialTemperature);
				mp->getMassParticles().front()->updateTemperature(initialTemperature);
				mp->setVelocity(this->initialVelocity);
				addParticle(mp);
			}
		}
	}
}