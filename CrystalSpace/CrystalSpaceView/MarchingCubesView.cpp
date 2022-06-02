#include "MarchingCubesView.h"

#include "../CrystalSpace/MarchingCubesAlgo.h"
#include "CrystalScene/Scene/VolumeScene.h"
#include "../../Crystal/Shape/TriangleMeshBuilder.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Space;

MarchingCubesView::MarchingCubesView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas)
{
}

/*
void MarchingCubesView::onShow()
{
}
*/

void MarchingCubesView::onOk()
{
	const Box3d box(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	//Volume<double> v(box, { 100, 100, 100 });

	SparseVolumed v({ 1,1,1 }, 1000000);

	const auto center = box.getCenter();
	const auto radius = 5.0;
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			for (int k = 0; k < 100; ++k) {
				const auto distanceSquared = Math::getDistanceSquared(v.getPositionAt({ i, j, k }), center);
				if (distanceSquared < radius * radius) {
					const auto distance = ::sqrt(distanceSquared);
					const auto value = 1.0 - distance / radius;
					auto n = v.createNode({ i,j,k });
					n->setValue(value);
					//v.setValue(i, j, k, value);
				}
			}
		}
	}

	MarchingCubesAlgo algo;
	algo.build(v, 0.30f);
	const auto& triangles = algo.getTriangles();
	TriangleMeshBuilder builder;
	for (const auto& t : triangles) {
		builder.add(t);
	}
	auto scene = new TriangleMeshScene(getWorld()->getNextSceneId(), "", std::move(builder.build()));

	scene->getPresenter()->createView(getWorld()->getRenderer());
	getWorld()->getScenes()->addScene(scene);
}