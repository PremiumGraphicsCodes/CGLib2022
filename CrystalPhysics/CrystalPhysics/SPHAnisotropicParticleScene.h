#pragma once

#include "CrystalScene/Scene/IScene.h"
#include "SPHAnisotropicParticleScenePresenter.h"

namespace Crystal {
	namespace Physics {
		class SPHAnisotropicParticle;

class SPHAnisotropicParticleScene : public Scene::IScene
{
public:
	SPHAnisotropicParticleScene(const int id, const std::string& name);

	virtual ~SPHAnisotropicParticleScene();

	//Space::SparseVolumef* getShape() const { return shape.get(); }

	//void resetShape(std::unique_ptr<Space::SparseVolumef> shape) { this->shape = std::move(shape); }

	Scene::SceneType getType() const { return Scene::SceneType("SPHAnisotropicParticleScene"); }

	Scene::IPresenter* getPresenter() { return presenter.get(); }

	Math::Box3dd getBoundingBox() const override;

	void addParticle(SPHAnisotropicParticle* mp) { particles.push_back(mp); }

	std::list<SPHAnisotropicParticle*> getParticles() const { return particles; }

	void clearParticles();

private:
	std::list<SPHAnisotropicParticle*> particles;
	std::unique_ptr<SPHAnisotropicParticleScenePresenter> presenter;
};


	}
}