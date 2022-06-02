#pragma once

#include "CrystalScene/Scene/IScene.h"

#include "SPHFlameParticle.h"
#include "SPHFlameScenePresenter.h"

namespace Crystal {
	namespace Physics {

class SPHFlameScene : public Scene::IScene
{
public:
	SPHFlameScene(const int id, const std::string& name);

	~SPHFlameScene() {}

	static constexpr auto Type = "SPHFlame";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter() { return presenter.get(); }

	void setPresenter(std::unique_ptr<SPHFlameScenePresenter> presenter);

	void addParticle(SPHFlameParticle* mp) { particles.push_back(mp); }

	std::list<SPHFlameParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3dd getBoundingBox() const override;

private:
	std::list<SPHFlameParticle*> particles;
	std::unique_ptr<SPHFlameScenePresenter> presenter;
};

	}
}
