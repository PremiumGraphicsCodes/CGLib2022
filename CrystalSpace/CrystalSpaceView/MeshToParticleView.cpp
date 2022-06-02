#include "MeshToParticleView.h"

#include "../CrystalSpace/MeshToParticleConverter.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalScene/Scene/PolygonMeshScene.h"
#include "Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::UI;

MeshToParticleView::MeshToParticleView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	//polygonMeshSelectView("PolygonMesh", model, canvas),
	divideLengthView("DivideLength", 1.0)
{
	//add(&polygonMeshSelectView);
	add(&divideLengthView);
}

void MeshToParticleView::onOk()
{
	PolygonMeshBuilder builder;
	const Box3d box(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	builder.add(box, 2, 2, 2);
	auto mesh = builder.build();

	MeshToParticleConverter converter;
	converter.subdivide(*mesh, 1.0);
	const auto positions = converter.getPositions();

	auto ps = std::make_unique<ParticleSystem<ParticleAttribute>>();
	ParticleAttribute attr;
	attr.color = ColorRGBAf(0, 0, 0, 0);
	for (auto p : positions) {
		ps->add(p, attr);
	}
	ParticleSystemScene* scene = new ParticleSystemScene(getWorld()->getNextSceneId(), "", std::move(ps));
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer());
}