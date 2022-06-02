#include "WFCircleView.h"

#include "../../Crystal/Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFCircleView::WFCircleView(const std::string& name, World* world, Canvas* canvas) :
	IWFAddView(name, world, canvas),
	circleView("Circle"),
	unumView("UNum", 12)
{
	add(&circleView);
	add(&unumView);
}

void WFCircleView::onOk()
{
	const auto& circle = circleView.getValue();
	WireFrameBuilder builder;
	builder.add(circle, unumView.getValue());

	IWFAddView::addWireFrame(builder.getPositions(), builder.getEdges());
}