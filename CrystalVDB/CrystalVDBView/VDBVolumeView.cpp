#include "VDBVolumeView.h"

//#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBScene.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBVolumeView::VDBVolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	scaleView("Scale", 1.0)
{
	add(&scaleView);
}

void VDBVolumeView::onOk()
{
	auto volume = new VDBVolumeScene(getWorld()->getNextSceneId(), "VDBVolume");
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				const auto dist = i * i + j * j + k * k;
				const auto v = std::sqrt(dist) / 10.0;
				volume->setValue({ i,j,k }, v);
			}
		}
	}
	volume->setScale(scaleView.getValue());

	volume->getPresenter()->createView(getWorld()->getRenderer());
	//getWorld()->getScenes()->addScene(volume);

	auto scene = new VDBScene(getWorld()->getNextSceneId(), "VDBScene");
	scene->add(volume);
	getWorld()->getScenes()->addScene(scene);
}
