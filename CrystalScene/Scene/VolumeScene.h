#pragma once

#include "Crystal/Shape/Volume.h"

#include "VolumePresenter.h"

#include "IShapeScene.h"
#include <memory>

namespace Crystal {
	namespace Scene {
		class VolumePresenter;

class VolumeScene : public IShapeScene
{
public:
	VolumeScene(const int id, const std::string& name, std::unique_ptr<Shape::Volume<float>> shape);

	virtual void translate(const Math::Vector3dd& v) { shape->move(v); }

	virtual void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	virtual void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	virtual Math::Vector3dd getPosition(const int index) const { return Math::Vector3dd(0, 0, 0); };

	Math::Box3dd getBoundingBox() const { return shape->getBoundingBox(); }

	Shape::Volume<float>* getShape() const { return shape.get(); }

	SceneType getType() const { return SceneType("VolumeScene"); }

	IPresenter* getPresenter() { return presenter.get(); }

	void setPresenter(std::unique_ptr<VolumePresenter> presenter) { this->presenter = std::move(presenter); }

	//std::vector<Shape::Particle<double>> toParticles() const;

private:
	std::unique_ptr<Shape::Volume<float>> shape;
	std::unique_ptr<VolumePresenter> presenter;
};

	}
}