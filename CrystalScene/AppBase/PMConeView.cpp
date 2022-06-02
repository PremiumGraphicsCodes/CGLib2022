#include "PMConeView.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PMConeView::PMConeView(const std::string& name, World* world, Canvas* canvas) :
	IPMAddView(name, world, canvas),
	coneView("Cone")
{
	add(&coneView);
}

void PMConeView::onOk()
{
	PolygonMeshBuilder builder;
	//builder.add(coneView.getValue(), 1, 1, 1);
	IPMAddView::addPolygonMesh(builder);
}
