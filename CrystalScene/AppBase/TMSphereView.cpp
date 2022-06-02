#include "TMSphereView.h"

#include "../../Crystal/Shape/TriangleMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TMSphereView::TMSphereView(const std::string& name, World* world, Canvas* canvas) :
	ITMAddView(name, world, canvas),
	sphereView("Sphere"),
	unumView("UNum", 36),
	vnumView("VNum", 36)
{
	add(&sphereView);
	add(&unumView);
	add(&vnumView);
}

void TMSphereView::onOk()
{
	TriangleMeshBuilder builder;
	builder.add(sphereView.getValue(), unumView.getValue(), vnumView.getValue());

	ITMAddView::addTriangleMesh(std::move(builder.build()));
}
