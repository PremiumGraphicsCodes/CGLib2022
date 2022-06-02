#include "WFSphereView.h"

#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFSphereView::WFSphereView(const std::string& name, World* world, Canvas* canvas) :
	IWFAddView(name, world, canvas),
	sphereView("Sphere"),
	unumView("UNum", 12),
	vnumView("VNum", 12)
{
	add(&sphereView);
	add(&unumView);
	add(&vnumView);
}

void WFSphereView::onOk()
{
	WireFrameBuilder builder;
	builder.add(sphereView.getValue(), unumView.getValue(), vnumView.getValue());
	IWFAddView::addWireFrame(builder.getPositions(), builder.getEdges());
}
