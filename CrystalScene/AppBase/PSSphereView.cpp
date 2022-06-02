#include "PSSphereView.h"

#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"

#include "../Command/Command.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::UI;

PSSphereView::PSSphereView(const std::string& name, World* world, Canvas* canvas) :
	IPSAddView(name, world, canvas),
	sphereView("Sphere"),
	divideLengthView("DivLength", 0.1)
{
	add(&sphereView);
	add(&divideLengthView);
}

void PSSphereView::onOk()
{
	const auto& sphere = sphereView.getValue();
	const auto bb = sphere.getBoundingBox();

	std::vector<Vector3dd> positions;
	const auto& length = bb.getLength();
	const auto divLength = divideLengthView.getValue();
	const auto du = divLength / length.x;
	const auto dv = divLength / length.y;
	const auto dw = divLength / length.z;
	const auto tolerance = 1.0e-12;
	for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
		for (auto v = 0.0; v < 1.0 + tolerance; v += dv) {
			for (auto w = 0.0; w < 1.0 + tolerance; w += dw) {
				const auto p = bb.getPosition(u, v, w);
				if (sphere.isInside(p)) {
					positions.push_back(p);
				}
			}
		}
	}
	IPSAddView::addParticleSystem(positions);

	/*
	const auto& shape = sphereView.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	for (int i = 0; i < countView.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(shape.getPosition(u, v, 1.0));
	}
	IPSAddView::addParticleSystem(positions);
	*/
}
