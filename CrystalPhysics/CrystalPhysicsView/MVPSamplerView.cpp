#include "MVPSamplerView.h"
#include "../CrystalPhysics/MVP/MVPFluidScene.h"
#include "../CrystalPhysics/MVPSampler.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;
using namespace Crystal::UI;

MVPSamplerView::MVPSamplerView(const std::string& name, World* model, Canvas* canvas) :
	IView(name),
	world(model),
	canvas(canvas),
	splitButton("Split"),
	mergeButton("Merge")
{
	splitButton.setFunction([=]() { onSplit(); });
	add(&splitButton);

	mergeButton.setFunction([=]() { onMerge(); });
	add(&mergeButton);
}

void MVPSamplerView::onSplit()
{

}

void MVPSamplerView::onMerge()
{
	MVPFluidScene fluidScene(world->getNextSceneId(), "");
	{
		const auto radius = 0.20;
		const auto length = radius * 1.00;
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				for (int k = 0; k < 10; ++k) {
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto vp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
					auto mp = new MVPMassParticle(vp, p, 1.0f);
					mp->setParent(vp);
					vp->addMassParticle(mp);
					fluidScene.addParticle(vp);
				}
			}
		}
	}
	//getWorld()->getScenes()->addScene(this->fluidScene);
	//fluidScene->getPresenter()->createView(getWorld()->getRenderer());

	MVPSampler sampler;
	sampler.merge({ &fluidScene }, 0.80);
}
