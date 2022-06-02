#include "DFFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

DFFluidScene::DFFluidScene(const int id, const std::string& name) :
	Scene::IScene(id, name)
{
	controller = std::make_unique<DFFluidSceneController>(this);
}

void DFFluidScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3dd DFFluidScene::getBoundingBox() const
{
	Box3dd bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}