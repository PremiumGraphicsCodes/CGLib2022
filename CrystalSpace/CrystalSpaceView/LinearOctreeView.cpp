#include "LinearOctreeView.h"

#include "../CrystalSpace/LinearOctree.h"

#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "../../Crystal/Math/Ray3d.h"
#include "CrystalScene/Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

LinearOctreeView::LinearOctreeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas)
{
}

void LinearOctreeView::onOk()
{
	const Vector3dd dir(1, 1, 1);
	const Ray3d ray(Vector3dd(0, 0, 0), glm::normalize(dir));
	const Box3d space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));

	LinearOctree octree;
	octree.init(space, 4);

	for (int i = 0; i < 10; ++i) {
		const auto p = ray.getPosition(i);
		auto item = new LinearOctreeItem(Box3dd(p, p));
		octree.add(item);
	}

	const auto& table = octree.getTable();
	std::vector<Box3dd> boxes;
	for (int i = 0; i < table.size(); ++i) {
		if (table[i] != nullptr) {
			const auto b = octree.calculateAABB(LinearOctreeIndex(i));
			boxes.push_back(b);
		}
	}

	WireFrameBuilder wfBuilder;
	/*
	auto children = octree.toSerialList();
	for (auto c : children) {
		wfBuilder.build(c->getSpace());
	}
	*/
	for (auto b : boxes) {
		wfBuilder.add(b);
	}

	auto wf = wfBuilder.createWireFrame();
	WireFrameAttribute attr;
	attr.color = Crystal::Graphics::ColorRGBAf(1, 1, 1, 1);
	attr.width = 1.0;
	auto scene = new WireFrameScene(getWorld()->getNextSceneId(), "", std::move(wf), attr);
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer());
}