#include "PSBoxView.h"

#include "../../Crystal/Graphics/ColorRGBA.h"
#include "../Scene/ParticleSystemScene.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSBoxView::PSBoxView(const std::string& name, World* world, Canvas* canvas) :
	IPSAddView("PSBox", world, canvas),
	boxView("Box"),
	divideLengthView("DivideLength", 0.1)
{
	add(&boxView);
	add(&divideLengthView);
};

void PSBoxView::onOk()
{
	const auto& b = boxView.getValue();
	std::vector<Vector3dd> positions;
	const auto& length = b.getLength();
	const auto divLength = divideLengthView.getValue();
	const auto du = divLength / length.x;
	const auto dv = divLength / length.y;
	const auto dw = divLength / length.z;
	const auto tolerance = 1.0e-12;
	for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
		for (auto v = 0.0; v < 1.0 + tolerance; v += dv) {
			for (auto w = 0.0; w < 1.0 + tolerance; w += dw) {
				positions.push_back(b.getPosition(u, v, w));
			}
		}
	}
	/*
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	for (int i = 0; i < countView.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		const auto w = dist(mt);
	}
	*/
	IPSAddView::addParticleSystem(positions);
}