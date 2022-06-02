#include "PMSphereView.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PMSphereView::PMSphereView(const std::string& name, World* world, Canvas* canvas) :
	IPMAddView(name, world, canvas),
	sphereView("Sphere"),
	unumView("UNum", 36),
	vnumView("VNum", 36)
{
	add(&sphereView);
	add(&unumView);
	add(&vnumView);
}

void PMSphereView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add( sphereView.getValue(), unumView.getValue(), vnumView.getValue() );

	IPMAddView::addPolygonMesh(builder);
}
