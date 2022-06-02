#include "VDBSphereView.h"

//#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSphereView::VDBSphereView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	scaleView("Scale", 1.0)
{
	add(&scaleView);
}

void VDBSphereView::onOk()
{
	auto volume = new VDBVolumeScene(getWorld()->getNextSceneId(), "VDBSphere");
	for (int i = -5; i <= 5; ++i) {
		for (int j = -5; j <= 5; ++j) {
			for (int k = -5; k <= 5; ++k) {
				const auto dist = std::sqrt(i * i + j * j + k * k);
				const auto v = 1.0 - dist / 5.0;
				volume->setValue({ i,j,k }, v);
			}
		}
	}
	volume->setScale(scaleView.getValue());

	volume->getPresenter()->createView(getWorld()->getRenderer());
	getWorld()->getScenes()->addScene(volume);
}
