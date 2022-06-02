#include "WFTorusView.h"

#include "../../Crystal/Math/Torus3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFTorusView::WFTorusView(const std::string& name, World* world, Canvas* canvas) :
	IWFAddView(name, world, canvas),
	torusView("Torus"),
	unumView("UNum", 24),
	vnumView("VNum", 12)
{
	add(&unumView);
	add(&vnumView);
	add(&torusView);
}

void WFTorusView::onOk()
{
	/*
	WireFrameBuilder builder;
	builder.build(torusView.getValue(), unumView.getValue(), vnumView.getValue());
	IWFAddView::addWireFrame(builder.getPositions(), builder.getEdges());
	*/
}
