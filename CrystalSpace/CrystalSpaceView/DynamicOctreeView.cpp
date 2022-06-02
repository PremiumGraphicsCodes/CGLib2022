#include "DynamicOctreeView.h"

#include "../CrystalSpace/DynamicOctree.h"

#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Shape/Particle.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalScene/Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

DynamicOctreeView::DynamicOctreeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas)
{
}

void DynamicOctreeView::onOk()
{
	Particle<float> p1(Vector3dd(1, 1, 1), 1.0f);
	Particle<float> p2(Vector3dd(10, 10, 10), 1.0f);

	DynamicOctree octree(Box3dd(Vector3dd(0,0,0), Vector3dd(16,16,16)));
	octree.divide(1.0, { &p1, &p2 });

	const auto volumes = octree.toVolumes(1.0f);

	WireFrameBuilder wfBuilder;
	/*
	for (auto v : volumes) {
		wfBuilder.add(v->getBoundingBox());
	}
	*/

	octree.clear();
	for (auto v : volumes) {
		Crystal::Util::Array3d<int> indices(4,4,4);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				for (int k = 0; k < 4; ++k) {
					auto p = v->getCellPosition(i, j, k);
					indices.set(i,j,k, wfBuilder.createPosition(p));
				}
			}
		}
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					auto i1 = indices.get(i, j, k);
					auto i2 = indices.get(i+1, j, k);
					auto i3 = indices.get(i+1, j+1, k);
					auto i4 = indices.get(i, j+1, k);

					auto i6 = indices.get(i, j, k+1);
					auto i7 = indices.get(i+1, j, k+1);
					auto i8 = indices.get(i + 1, j + 1, k+1);
					auto i9 = indices.get(i, j + 1, k+1);

					wfBuilder.addEdge(WireFrameEdge(i1, i2));
					wfBuilder.addEdge(WireFrameEdge(i2, i3));
					wfBuilder.addEdge(WireFrameEdge(i3, i4));
					wfBuilder.addEdge(WireFrameEdge(i4, i1));

					wfBuilder.addEdge(WireFrameEdge(i6, i7));
					wfBuilder.addEdge(WireFrameEdge(i7, i8));
					wfBuilder.addEdge(WireFrameEdge(i8, i9));
					wfBuilder.addEdge(WireFrameEdge(i9, i6));

					wfBuilder.addEdge(WireFrameEdge(i1, i6));
					wfBuilder.addEdge(WireFrameEdge(i2, i7));
					wfBuilder.addEdge(WireFrameEdge(i3, i8));
					wfBuilder.addEdge(WireFrameEdge(i4, i9));

				}
			}
		}

		delete v;
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