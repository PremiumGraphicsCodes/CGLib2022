#include "VoxelSphereView.h"

#include "../../CrystalSpace/CrystalSpace/Voxel.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

VoxelSphereView::VoxelSphereView(const std::string& name, World* world, Canvas* canvas) :
	IVoxelAddView(name, world, canvas),
	sphereView("Sphere"),
	resolutionView("Resolution")
{
	add(&sphereView);
	add(&resolutionView);
	resolutionView.setValue(10);
}

void VoxelSphereView::onOk()
{
	const auto sphere = sphereView.getValue();
	const auto res = static_cast<size_t>(resolutionView.getValue());
	const std::array<size_t, 3> resolution = { res, res, res };
	auto sv = std::make_unique<Voxel>(sphere.getBoundingBox(), resolution);
	sv->fill(false);

	const auto center = sphere.getCenter();
	const auto rad = sphere.getRadius();
	for (int ix = 0; ix < resolution[0]; ++ix) {
		for (int iy = 0; iy < resolution[1]; ++iy) {
			for (int iz = 0; iz < resolution[2]; ++iz) {
				const auto p = sv->getCellPosition(ix, iy, iz);
				if (Crystal::Math::getDistanceSquared(p, center) < rad * rad) {
					sv->setValue(ix, iy, iz, true);
				}
			}
		}
	}

	IVoxelAddView::addVoxel(std::move(sv));
}
