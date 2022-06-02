#include "SolidBoxView.h"

#include "../../Crystal/Shape/Solid.h"
#include "../Scene/SolidScene.h"
#include "Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

SolidBoxView::SolidBoxView(const std::string& name, World* world, Canvas* canvas) :
	ISolidAddView(name, world, canvas),
	boxView("Box")
{
	add(&boxView);
}

void SolidBoxView::onOk()
{
	auto solid = std::make_unique<Solid>((std::make_unique<Box3dd>()));
	ISolidAddView::addSolid(std::move(solid));
}