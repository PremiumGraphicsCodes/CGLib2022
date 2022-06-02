#include "WFEllipsoidView.h"

#include "../../Crystal/Math/Ellipsoid3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFEllipsoidView::WFEllipsoidView(const std::string& name, World* world, Canvas* canvas) :
	IWFAddView(name, world, canvas),
	ellipsoidView("Ellipsoid"),
	unumView("UNum", 12),
	vnumView("VNum", 12)
{
	add(&ellipsoidView);
	add(&unumView);
	add(&vnumView);
}

void WFEllipsoidView::onOk()
{
	WireFrameBuilder builder;
	builder.add(ellipsoidView.getValue(), unumView.getValue(), vnumView.getValue());
	IWFAddView::addWireFrame(builder.getPositions(), builder.getEdges());
}
