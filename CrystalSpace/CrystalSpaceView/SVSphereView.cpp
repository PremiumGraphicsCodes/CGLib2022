#include "SVSphereView.h"

#include "../../CrystalSpace/CrystalSpace/SparseVolume.h"
#include "CrystalSpace/CrystalSpace/SparseVolumeBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

SVSphereView::SVSphereView(const std::string& name, World* world, Canvas* canvas) :
	ISVAddView(name, world, canvas),
	sphereView("Sphere"),
	cellLengthView("Resolution", 1.0f)
{
	add(&sphereView);
	sphereView.setValue(Sphere3dd(Vector3dd(0, 0, 0), 5.0));
	add(&cellLengthView);
}

void SVSphereView::onOk()
{
	const auto sphere = sphereView.getValue();
	const auto cellLength = cellLengthView.getValue();

	SparseVolumeBuilder builder;
	builder.build({ cellLength, cellLength, cellLength }, 100);
	builder.add(sphere);
	auto sv = builder.get();
	auto nodes = sv->getNodes();
	for (auto n : nodes) {
		n->setValue(1.0f);
	}
	/*
	auto sv = std::make_unique<SparseVolumed>(sphere.getBoundingBox(), resolution, res*res*res);

	const auto center = sphere.getCenter();
	const auto rad = sphere.getRadius();
	for (int ix = 0; ix < resolution[0]; ++ix) {
		for (int iy = 0; iy < resolution[1]; ++iy) {
			for (int iz = 0; iz < resolution[2]; ++iz) {
				const std::array<int,3> index = { ix, iy, iz };
				const auto p = sv->getPositionAt(index);
				if(Crystal::Math::getDistanceSquared(p, center) < rad * rad) {
					const auto d = Crystal::Math::getDistance(p, center) / rad;
					sv->createNode(index);
					auto n = sv->findNode(index);
					n->setValue(d);
				}
			}
		}
	}
	*/

	ISVAddView::addVolume(std::move(sv));
}
