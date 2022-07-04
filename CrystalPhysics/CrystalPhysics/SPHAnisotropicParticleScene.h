#pragma once

#include "CrystalScene/Scene/IScene.h"
#include "ISPHAnisotropicParticlePresenter.h"

namespace Crystal {
	namespace Physics {
		class SPHAnisotropicParticle;

class SPHAnisotropicParticleScene : public Scene::IScene
{
public:
	SPHAnisotropicParticleScene(const int id, const std::string& name);

	virtual ~SPHAnisotropicParticleScene();

	Scene::SceneType getType() const { return Scene::SceneType("SPHAnisotropicParticleScene"); }

	Scene::IPresenter* getPresenter() { return presenter.get(); }

	void setPresenter(std::unique_ptr<ISPHAnisotropicParticlePresenter> presenter) { this->presenter = std::move(presenter); }

	Math::Box3dd getBoundingBox() const override;

	void addParticle(SPHAnisotropicParticle* mp) { particles.push_back(mp); }

	std::list<SPHAnisotropicParticle*> getParticles() const { return particles; }

	void clearParticles();

private:
	std::list<SPHAnisotropicParticle*> particles;
	std::unique_ptr<ISPHAnisotropicParticlePresenter> presenter;
};


	}
}