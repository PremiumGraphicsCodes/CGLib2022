#include "SPHAnisotropicParticleScene.h"

#include "SurfaceConstruction/SPHAnisotropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

SPHAnisotropicParticleScene::SPHAnisotropicParticleScene(const int id, const std::string& name) :
	IScene(id, name)
{
	this->presenter = std::make_unique<SPHAnisotropicParticleScenePresenter>(this);
}

SPHAnisotropicParticleScene::~SPHAnisotropicParticleScene()
{
	clearParticles();
}

void SPHAnisotropicParticleScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3dd SPHAnisotropicParticleScene::getBoundingBox() const
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
