#include "SVBoxView.h"

#include "../../CrystalSpace/CrystalSpace/SparseVolume.h"
#include "CrystalSpace/CrystalSpace/SparseVolumeBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

SVBoxView::SVBoxView(const std::string& name, World* world, Canvas* canvas) :
	ISVAddView(name, world, canvas),
	boxView("Box"),
	cellLengthView("Resolution", 1.0f)
{
	add(&boxView);
	boxView.setValue(Box3dd(Vector3dd(-10, -10, -10), Vector3dd(10,10,10)));
	add(&cellLengthView);
}

void SVBoxView::onOk()
{
	const auto box = boxView.getValue();
	const auto cellLength = cellLengthView.getValue();

	SparseVolumeBuilder builder;
	builder.build({ cellLength, cellLength, cellLength }, 100);
	builder.add(box);
	auto sv = builder.get();
	auto nodes = sv->getNodes();
	for (auto n : nodes) {
		n->setValue(1.0f);
	}

	ISVAddView::addVolume(std::move(sv));
}
