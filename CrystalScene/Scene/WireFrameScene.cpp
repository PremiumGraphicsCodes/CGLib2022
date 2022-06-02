#include "WireFrameScene.h"

#include "WireFramePresenter.h"

#include "Crystal/Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

WireFrameScene::WireFrameScene() :
	IShapeScene(-1)
{
	this->presenter = std::make_unique<WireFramePresenter>(this);
}

WireFrameScene::WireFrameScene(const int id, const std::string& name, std::unique_ptr<WireFrame> shape, const WireFrameAttribute& attribute) :
	IShapeScene(id, name),
	shape(std::move(shape)),
	attribute(attribute)
{
	this->presenter = std::make_unique<WireFramePresenter>(this);
}

void WireFrameScene::translate(const Vector3dd& v)
{
	shape->move(v);
}

void WireFrameScene::transform(const Matrix3dd& m)
{
	shape->transform(m);
}

void WireFrameScene::transform(const Matrix4dd& m)
{
	shape->transform(m);
}

std::vector<Vector3dd> WireFrameScene::getAllVertices() const
{
	return shape->getPositions();
}

Box3dd WireFrameScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}