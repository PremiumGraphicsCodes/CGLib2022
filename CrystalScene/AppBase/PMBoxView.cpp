#include "PMBoxView.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PMBoxView::PMBoxView(const std::string& name, World* world, Canvas* canvas) :
	IPMAddView(name, world, canvas),
	boxView("Box")
{
	add(&boxView);
}

void PMBoxView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(boxView.getValue(), 2, 2, 2);

	IPMAddView::addPolygonMesh(builder);
}
