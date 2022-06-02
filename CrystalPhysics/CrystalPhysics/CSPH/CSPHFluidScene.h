#pragma once

#include "CrystalScene/Scene/IScene.h"

#include "CSPHParticle.h"
#include "CSPHFluidSceneController.h"

namespace Crystal {
	namespace Physics {

class CSPHFluidScene : public Scene::IScene
{
public:
	CSPHFluidScene(const int id, const std::string& name);

	~CSPHFluidScene() {}

	static constexpr auto Type = "CSPHFluid";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter() { return controller.get(); }

	void addParticle(CSPHParticle* mp) { particles.push_back(mp); }

	std::list<CSPHParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3dd getBoundingBox() const override;

private:
	std::list<CSPHParticle*> particles;
	std::unique_ptr<CSPHFluidSceneController> controller;
};

	}
}
