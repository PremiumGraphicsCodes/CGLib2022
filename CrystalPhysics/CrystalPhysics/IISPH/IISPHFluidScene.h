#pragma once

#include "CrystalScene/Scene/IScene.h"

#include "IISPHParticle.h"
#include "IISPHFluidSceneController.h"

namespace Crystal {
	namespace Physics {
	//	class KFFluidSceneController;

class IISPHFluidScene : public Scene::IScene
{
public:
	IISPHFluidScene(const int id, const std::string& name);

	~IISPHFluidScene() {}

	static constexpr auto Type = "IISPHFluid";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter() {
		return controller.get();
	}//controller.get(); }

	void addParticle(IISPHParticle* mp) {
		//mp->setScene(this);
		particles.push_back(mp);
	}

	std::list<IISPHParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3dd getBoundingBox() const override;


private:
	std::list<IISPHParticle*> particles;
	std::unique_ptr<IISPHFluidSceneController> controller;
};

	}
}
