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
		const auto b = c->getBoundingBox();
		bb.add(b);
	}
	if (bb.isDegenerated()) {
		return Box3dd(Vector3dd(-0.5,-0.5,-0.5), Vector3dd(0.5, 0.5, 0.5));
	}

	return bb;
}



