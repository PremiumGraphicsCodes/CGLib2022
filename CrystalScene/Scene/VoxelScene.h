#pragma once

#include "Crystal/Shape/Volume.h"

#include "VoxelPresenter.h"

#include "IShapeScene.h"
#include <memory>

namespace Crystal {
	namespace Scene {
		class VoxelPresenter;

class VoxelScene : public IShapeScene
{
public:
	VoxelScene(const int id, const std::string& name, std::unique_ptr<Shape::Volume<bool>> shape);

	virtual void translate(const Math::Vector3dd& v) { shape->move(v); }

	virtual void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	virtual void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	virtual Math::Vector3dd getPosition(const int index) const { return Math::Vector3dd(0, 0, 0); };

	Math::Box3dd getBoundingBox() const { return shape->getBoundingBox(); }

	void setShape(std::unique_ptr<Shape::Volume<bool>> shape) { this->shape = std::move(shape); }

	const Shape::Volume<bool>* getShape() const { return shape.get(); }

	SceneType getType() const { return SceneType("VoxelScene"); }

	IPresenter* getPresenter() { return presenter.get(); }

	void setPresenter(std::unique_ptr<VoxelPresenter> presenter) { this->presenter = std::move(presenter); }

	//std::vector<Shape::Particle<double>> toParticles() const;

private:
	std::unique_ptr<Shape::Volume<bool>> shape;
	std::unique_ptr<VoxelPresenter> presenter;
};

	}
}