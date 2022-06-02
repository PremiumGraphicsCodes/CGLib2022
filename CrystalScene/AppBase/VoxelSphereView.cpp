#include "VoxelSphereView.h"

#include "../../Crystal/Shape/Volume.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

VoxelSphereView::VoxelSphereView(const std::string& name, World* world, Canvas* canvas) :
	IVoxelAddView(name, world, canvas),
	boxView("Box"),
	resolutionView("Resolution")
{
	add(&boxView);
	add(&resolutionView);
	resolutionView.setValue(10);
}

void VoxelSphereView::onOk()
{
	const auto box = boxView.getValue();
	const auto res = static_cast<size_t>(resolutionView.getValue());
	std::array<size_t, 3> resolution = { res, res, res };
	auto v = std::make_unique<Volume<bool>>(box, resolution);

	const auto corner = box.getPosition(0, 0, 0);
	const auto center = box.getCenter();
	const auto radius = 0.5;//glm::distance(center, corner);
	for (int i = 0; i < resolution[0]; ++i) {
		for (int j = 0; j < resolution[1]; ++j) {
			for (int k = 0; k < resolution[2]; ++k) {
				const auto p = v->getCellPosition(i, j, k);
				const auto d = glm::distance(p, center);
				if (d < radius) {
					v->setValue(i, j, k, true);
				}
			}
		}
	}

	//const auto center = box.getCenter();
	//v = std::make_unique<Volume<float>> 

	IVoxelAddView::addVoxel(std::move(v));
}
