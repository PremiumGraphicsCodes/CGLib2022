#include "VDBPSBoxView.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "../CrystalVDB/VDBPointsScene.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBPSBox::VDBPSBox(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	sphereView("Sphere"),
	divideLengthView("DivideLength", 0.1)
{
	add(&sphereView);
	add(&divideLengthView);
}

void VDBPSBox::onOk()
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
	auto scene = new VDBPointsScene(getWorld()->getNextSceneId(), "VDBPS");
	scene->create(positions);
	scene->getPresenter()->createView(getWorld()->getRenderer());
	getWorld()->getScenes()->addScene(scene);
}
