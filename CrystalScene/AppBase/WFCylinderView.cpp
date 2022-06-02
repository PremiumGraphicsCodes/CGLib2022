#include "WFCylinderView.h"

#include "../../Crystal/Math/Cylinder3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFCylinderView::WFCylinderView(const std::string& name, World* world, Canvas* canvas) :
	IWFAddView(name, world, canvas),
	cylinderView("Cylinder"),
	unumView("UNum", 12),
	vnumView("VNum", 1)
{
	add(&cylinderView);
	add(&unumView);
	add(&vnumView);
}

void WFCylinderView::onOk()
{
	WireFrameBuilder builder;
	builder.add(cylinderView.getValue(), unumView.getValue(), vnumView.getValue());
	IWFAddView::addWireFrame(builder.getPositions(), builder.getEdges());
}
