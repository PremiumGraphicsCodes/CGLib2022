#include "ToVDBVolumeView.h"

#include "../CrystalVDB/VDBVolumeConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"

#include "../../CrystalSpace/CrystalSpace/SparseVolumeScene.h"

#include <iostream>

using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::UI;
using namespace Crystal::VDB;

ToVDBVolumeView::ToVDBVolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	sphereView("Sphere"),
	resolutionView("Resolution")
{
	add(&sphereView);
	add(&resolutionView);
	resolutionView.setValue(10);
}

void ToVDBVolumeView::onOk()
{
	std::array<int, 3> resolution =
	{
		resolutionView.getValue(),
		resolutionView.getValue(),
		resolutionView.getValue()
	};

	const auto sphere = sphereView.getValue();
	const auto bb = sphere.getBoundingBox();
	auto sv = std::make_unique<SparseVolumef>(Crystal::Math::Vector3df(1,1,1), resolution[0] * resolution[1] * resolution[2]);
	const auto center = sphere.getCenter();
	for (int i = 0; i < resolution[0]; ++i) {
		for (int j = 0; j < resolution[1]; ++j) {
			for (int k = 0; k < resolution[2]; ++k) {
				const auto p = sv->getPositionAt({ i,j,k });
				const auto d = glm::distance(p, center);
				if (d < sphere.getRadius()) {
					const auto v = d / sphere.getRadius();
					sv->createNode({ i,j,k });
					auto n = sv->findNode({ i,j,k });
					n->setValue(v);
				}
			}
		}
	}

	SparseVolumeScene svScene(-1, "Original", std::move(sv));

	VDBVolumeScene* dest = new VDBVolumeScene();
	VDBVolumeConverter converter;
	converter.fromSparseVolume(*svScene.getShape(), dest);
	dest->getPresenter()->createView(getWorld()->getRenderer());
	getWorld()->getScenes()->addScene(dest);
}