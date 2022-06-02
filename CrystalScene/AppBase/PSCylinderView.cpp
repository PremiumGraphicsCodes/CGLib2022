#include "PSCylinderView.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSCylinderView::PSCylinderView(const std::string& name, World* world, Canvas* canvas) :
	IPSAddView(name, world, canvas),
	cylinderView("Cylinder"),
	countView("Count", 10000)
{
	add(&cylinderView);
	add(&countView);
}

void PSCylinderView::onOk()
{
	const auto& cylinder = cylinderView.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	for (int i = 0; i < countView.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(cylinder.getPosition(u, v, 1.0));
	}
	IPSAddView::addParticleSystem(positions);
}

