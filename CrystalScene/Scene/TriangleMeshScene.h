#pragma once

#include "IShapeScene.h"
#include "Crystal/Shape/TriangleMesh.h"
#include "ITMPresenter.h"

namespace Crystal {
	namespace Scene {

class TriangleMeshScene : public IShapeScene
{
public:
	explicit TriangleMeshScene(const int id);

	TriangleMeshScene(const int id, const std::string& name, std::unique_ptr<Shape::TriangleMesh> shape);

	void translate(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	std::vector<Math::Vector3dd> getAllVertices() const { return {}; }

	SceneType getType() const override { return SceneTypeLabels::TriangleMeshScene; }

	ITMPresenter* getPresenter() { return presenter.get(); }

	const Shape::TriangleMesh* getShape() const { return shape.get(); }

	void setShape(std::unique_ptr<Shape::TriangleMesh> shape) { this->shape = std::move(shape); }

	Math::Box3dd getBoundingBox() const override { return shape->getBoundingBox(); }

private:
	std::unique_ptr<Shape::TriangleMesh> shape;
	std::unique_ptr<ITMPresenter> presenter;
};

	}
}