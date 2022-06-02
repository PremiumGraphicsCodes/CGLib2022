#include "SolidScene.h"

using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

SolidScene::SolidScene() :
	IShapeScene(-1, ""),
	color(ColorRGBAf(0,0,0,0)),
	shape(nullptr)
{
	presenter = std::make_unique<SolidAsWFPresenter>(this);
}

SolidScene::SolidScene(const int id, const std::string& name, std::unique_ptr<Solid> shape) :
	IShapeScene(id, name),
	color(ColorRGBAf(0, 0, 0, 0)),
	shape(std::move(shape))
{
	presenter = std::make_unique<SolidAsWFPresenter>(this);
}
