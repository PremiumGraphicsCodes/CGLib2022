#include "Scene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

Scene::Scene(const int id, const std::string& name) :
	IScene(id, name)
{
}


Scene::~Scene()
{
}

Box3dd Scene::getBoundingBox() const
{
	Box3dd bb = Box3dd::createDegeneratedBox();
	for (auto c : children) {
		if (bb.isDegenerated()) {
			bb = c->getBoundingBox();
			continue;
		}
		auto b = c->getBoundingBox();
		if (b.isDegenerated()) {
			continue;
		}
		bb.add(b);
	}
	if (bb.isDegenerated()) {
		return Box3dd();
	}

	return bb;
}



