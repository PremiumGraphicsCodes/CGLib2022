#pragma once

#include "CrystalScene/Scene/IParticleSystemScene.h"

#include "MVPFluidScenePresenter.h"

namespace Crystal {
	namespace Physics {
		class MVPBoundaryParticle;
		class MVPFluidScenePresenter;

class MVPBoundaryScene : public Scene::IParticleSystemScene
{
public:
	MVPBoundaryScene(const int id, const std::string& name);

	~MVPBoundaryScene();

	static constexpr auto Type = "KFBoundary";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter() { return nullptr; }//controller.get(); }

	/*
	void addParticle(KFMacroParticle* mp) {
		mp->setScene(this);
		particles.push_back(mp);
	}
	*/

	std::vector<MVPBoundaryParticle*> getParticles() const { return particles; }

	Math::Box3dd getBoundingBox() const override;

	void setPressureCoe(const float coe) { this->pressureCoe = coe; }

	float getPressureCoe() const { return this->pressureCoe; }

	void setViscosityCoe(const float coe) { this->viscosityCoe = coe; }

	float getViscosityCoe() const { return this->viscosityCoe; }

	void translate(const Math::Vector3dd& v) override { ; }

	void transform(const Math::Matrix3dd& m) override { ; }

	void transform(const Math::Matrix4dd& m) override { ; }

	std::vector<Math::Vector3dd> getPositions() const override;

private:
	std::vector<MVPBoundaryParticle*> particles;
	float pressureCoe;
	float viscosityCoe;
	//std::unique_ptr<KFFluidScenePresenter> controller;
};


	}
}
