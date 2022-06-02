#include "MPSFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

MPSFluidScene::MPSFluidScene(const int id, const std::string& name) :
	Scene::IScene(id, name)
{
	controller = std::make_unique<MPSFluidSceneController>(this);
}

void MPSFluidScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3dd MPSFluidScene::getBoundingBox() const
{
	if (particles.empty()) {
		return Box3dd::createDegeneratedBox();
	}
	Box3dd bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}