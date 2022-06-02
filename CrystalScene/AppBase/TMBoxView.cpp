#include "TMBoxView.h"

#include "../../Crystal/Shape/TriangleMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TMBoxView::TMBoxView(const std::string& name, World* world, Canvas* canvas) :
	ITMAddView(name, world, canvas),
	boxView("Box")
{
	add(&boxView);
}

void TMBoxView::onOk()
{
	TriangleMeshBuilder builder;
	builder.add(boxView.getValue(), 2, 2, 2);

	ITMAddView::addTriangleMesh(builder.build());
}
