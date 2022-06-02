#include "PBFluidScene.h"

#include "PBSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

PBFluidScene::PBFluidScene(const int id, const std::string& name) :
	IScene(id, name),
	kernel(1.0f),
	restDensity(1.0f),
	stiffness(0.05f),
	viscosity(0.1f),
	_isBoundary(false)
{
	this->controller = std::make_unique<PBFluidSceneController>(this);
}

PBFluidScene::~PBFluidScene()
{
	clearParticles();
}

void PBFluidScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3dd PBFluidScene::getBoundingBox() const
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

void PBFluidScene::setEffectLength(const float effectLength)
{
	this->kernel = SPHKernel(effectLength);
}

void PBFluidScene::setRestDensity(const float restDensity)
{
	this->restDensity = restDensity;
}
