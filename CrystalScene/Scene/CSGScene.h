#pragma once

#include "IShapeScene.h"
#include "Crystal/Shape/Solid.h"

#include "ParticleSystemPresenter.h"

namespace Crystal {
	namespace Scene {

		/*
class CSGScene : public IShapeScene
{
public:
	CSGScene();

	//ParticleSystemScene(const int id, const std::string& name);

	CSGScene(const int id, const std::string& name);

	~CSGScene() {};

	//Shape::ParticleSystem<ParticleAttribute>* getShape() const { return shape.get(); }

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) override { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) override { shape->transform(m); }

	SceneType getType() const override { return SceneType::CSGScene; }

	Math::Box3d getBoundingBox() const override;

	Math::Vector3dd getPosition(const int index) const override;

	IShapeScene* clone() const override;

	void setAttribute(const ParticleAttribute& attribute);

	ParticleSystemPresenter* getPresenter() { return controller.get(); }

private:
	std::unique_ptr< Shape::ParticleSystem<ParticleAttribute> > shape;
	std::unique_ptr< ParticleSystemPresenter > controller;
};
*/

	}
}