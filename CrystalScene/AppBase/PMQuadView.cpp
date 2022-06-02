#include "PMQuadView.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::UI;

PMQuadView::PMQuadView(const std::string& name, World* world, Canvas* canvas) :
	IPMAddView(name, world, canvas),
	quadView("Quad")
{
	add(&quadView);
}

void PMQuadView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(quadView.getValue(), 1, 1);

	IPMAddView::addPolygonMesh(builder);
}
