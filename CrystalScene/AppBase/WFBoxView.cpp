#include "WFBoxView.h"

#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../Scene/World.h"
#include "../Scene/WireFrameScene.h"
#include "Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFBoxView::WFBoxView(const std::string& name, World* world, Canvas* canvas) :
	IWFAddView(name, world, canvas),
	boxView("Box")
{
	add(&boxView);
}

void WFBoxView::onOk()
{
	WireFrameBuilder builder;
	builder.add(boxView.getValue());
	IWFAddView::addWireFrame(builder.getPositions(), builder.getEdges());
}