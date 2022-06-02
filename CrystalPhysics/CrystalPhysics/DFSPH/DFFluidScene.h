#pragma once

#include "CrystalScene/Scene/IScene.h"

#include "DFSPHParticle.h"
#include "DFFluidSceneController.h"

namespace Crystal {
	namespace Physics {
	//	class KFFluidSceneController;

class DFFluidScene : public Scene::IScene
{
public:
	DFFluidScene(const int id, const std::string& name);

	~DFFluidScene() {}

	static constexpr auto Type = "DFFluid";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter() {
		return controller.get();
	}//controller.get(); }

	void addParticle(DFSPHParticle* mp) {
		//mp->setScene(this);
		particles.push_back(mp);
	}

	std::list<DFSPHParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3dd getBoundingBox() const override;


private:
	std::list<DFSPHParticle*> particles;
	std::unique_ptr<DFFluidSceneController> controller;
};

	}
}
