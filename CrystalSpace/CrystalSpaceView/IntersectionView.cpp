#include "IntersectionView.h"

#include "Crystal/Math/Ray3d.h"
#include "Crystal/Math/Sphere3d.h"
#include "Crystal/Math/Triangle3d.h"

#include "Crystal/Shape/WireFrameBuilder.h"
#include "Crystal/Shape/PolygonMeshBuilder.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalScene/Scene/PolygonMeshScene.h"

#include "../CrystalSpace/IntersectionCalculator.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

IntersectionView::IntersectionView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	rayTriangleButton("RayTriangle"),
	tolerance("Tolerance", 1.0e-12)
{
	rayTriangleButton.setFunction([=]() { onRayTriangle(); });

	add(&rayTriangleButton);
}

void IntersectionView::onRayTriangle()
{
	PolygonMeshBuilder builder;
//	const Sphere3dd sphere(Vector3dd(0,0,0), 10);
//	builder.add(sphere, 20, 20);
	const Box3dd box(Vector3dd(-10, -10, -10), Vector3dd(10, 10, 10));
	builder.add(box, 2, 2, 2);
	auto mesh = builder.build();

	const Ray3d ray(Vector3dd(-100, 0, 0), Vector3dd(1, 0, 0));

	IntersectionCalculator calculator;
	const auto faces = mesh->getFaces();
	for (const auto& f : faces) {
		const auto t = f.toTriangle(mesh->getPositions());
		calculator.calculateIntersection(ray, t, tolerance.getValue());
	}

	const auto& intersections = calculator.getIntersections();
	std::vector<Math::Vector3dd> positions;
	for (const auto& i : intersections) {
		const auto& p = i.position;
		positions.push_back(p);
	}
	auto ps = std::make_unique<ParticleSystem<ParticleAttribute>>();

	ParticleAttribute attr;
	attr.color = glm::vec4(1.0, 0.0, 0.0, 0.0);
	attr.size = 100.0f;
	for (auto p : positions) {
		ps->add(p, attr);
	}

	auto scene = new ParticleSystemScene(getWorld()->getNextSceneId(), "", std::move(ps));
	getWorld()->getScenes()->addScene(scene);
	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer());
}

void IntersectionView::onOk()
{
	/*
	auto repository = getWorld();
	auto obj1 = repository->getScenes()->findSceneById<PolygonMeshScene*>(mesh1.getId());
	auto obj2 = repository->getScenes()->findSceneById<PolygonMeshScene*>(mesh2.getId());
	if (obj1 == nullptr || obj2 == nullptr) {
		return;
	}

	/*
	IntersectionCalculator algo;
	const auto isFound = algo.calculateIntersection(*obj1->getShape(),*obj2->getShape(), tolerance.getValue());
	if (isFound) {
		const auto& intersections = algo.getIntersections();
		std::vector<Math::Vector3dd> positions;
		for (const auto& i : intersections) {
			const auto& p = i.position;
			positions.push_back(p);
		}
		ParticleAttribute attr;
		attr.color = glm::vec4(1.0, 0.0, 0.0, 0.0);
		attr.size = 1.0f;
		//repository->getSceneFactory()->createParticleSystemScene(positions, attr, "intersections");
		//getWorld()->updateViewModel();
	}
	*/
}

