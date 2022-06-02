#include "VolSphereView.h"

#include "../../Crystal/Shape/Volume.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

VolSphereView::VolSphereView(const std::string& name, World* world, Canvas* canvas) :
	IVolAddView(name, world, canvas),
	boxView("Box"),
	resolutionView("Resolution")
{
	add(&boxView);
	add(&resolutionView);
	resolutionView.setValue(10);
}

void VolSphereView::onOk()
{
	const auto box = boxView.getValue();
	const auto res = static_cast<size_t>( resolutionView.getValue() );
	std::array<size_t, 3> resolution = { res, res, res };
	auto v = std::make_unique<Volume<float>>(box, resolution);

	const auto corner = box.getPosition(0, 0, 0);
	const auto center = box.getCenter();
	const auto radius = glm::distance(center, corner);
	for (size_t i = 0; i < resolution[0]; ++i) {
		for (size_t j = 0; j < resolution[1]; ++j) {
			for (size_t k = 0; k < resolution[2]; ++k) {
				const auto p = v->getCellPosition(i,j,k);
				const auto value = glm::distance(p, center) / radius;
				v->setValue(i, j, k, value);
			}
		}
	}

	//const auto center = box.getCenter();
	//v = std::make_unique<Volume<float>> 
	
	IVolAddView::addVolume(std::move(v));
}
