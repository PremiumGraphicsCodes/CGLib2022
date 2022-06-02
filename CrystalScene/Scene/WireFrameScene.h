#pragma once

#include "IShapeScene.h"
#include "WireFrameAttribute.h"
#include "IWireFramePresenter.h"

#include "Crystal/Math/Line3d.h"
#include "Crystal/Shape/WireFrame.h"

namespace Crystal {
	namespace Scene {

class WireFrameScene : public IShapeScene
{
public:
	WireFrameScene();

	WireFrameScene(const int id, const std::string& name, std::unique_ptr<Shape::WireFrame> shape, const WireFrameAttribute& attribute);

	~WireFrameScene() {};

	WireFrameAttribute getAttribute() const { return attribute; }

	void translate(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	SceneType getType() const override { return SceneTypeLabels::WireFrameScene; }

	Math::Box3dd getBoundingBox() const override;

	std::vector<Math::Vector3dd> getAllVertices() const;

	Shape::WireFrame* getShape() { return shape.get(); }

	IPresenter* getPresenter() { return presenter.get(); }

private:
	std::unique_ptr<Shape::WireFrame> shape;
	WireFrameAttribute attribute;
	std::unique_ptr<IWireFramePresenter> presenter;
};

	}
}