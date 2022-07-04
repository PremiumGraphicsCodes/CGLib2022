#include "SPHAnisotropyEstimatorView.h"

#include "../CrystalPhysics/SPHAnisotropyEstimator.h"
#include "../CrystalPhysics/SPHAnisotropicParticleScene.h"
#include "../CrystalPhysics/SPHAnisotropicParticleScenePresenter.h"

#include "Crystal/Math/Sphere3d.h"

#include "Crystal/IO/PLYFileReader.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Physics;


SPHAnisotropyEstimatorView::SPHAnisotropyEstimatorView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	particleRadiusView("ParticleRadius", 1.0f),
	searchRadiusView("SearchRadius", 2.5f),
	fileView("File")
{
	add(&particleRadiusView);
	add(&searchRadiusView);
	add(&fileView);
	fileView.addFilter("*.ply");
}

void SPHAnisotropyEstimatorView::onOk()
{
	SPHAnisotoropyEstimator estimator;

	const auto particleRadius = particleRadiusView.getValue();

	const Sphere3d sphere(Vector3dd(50, 50, 50), 10.0);
	const Box3d box = sphere.getBoundingBox();
	const auto center = sphere.getCenter();
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				const auto u = i / 10.0;
				const auto v = j / 10.0;
				const auto w = k / 10.0;
				const auto p = box.getPosition(u, v, w);
				if (sphere.isInside(p)) {
					estimator.add(p, particleRadius);
				}
			}
		}
	}

	const auto searchRadius = searchRadiusView.getValue();
	estimator.estimateAnIsotoropy(searchRadius);
	/*
	const auto filePath = fileView.getFileName();
	Crystal::IO::PLYFileReader reader;
	reader.read(filePath);
	const auto positions = reader.getPLY().vertices;
	for (const auto& v : positions) {
		const auto x = v.getValueAs<float>(0);
		const auto y = v.getValueAs<float>(1);
		const auto z = v.getValueAs<float>(2);
		Vector3df p(x, y, z);
		estimator.add(p, particleRadius);
	}

	estimator.estimateIsotoropy(searchRadius);
	//positions.emplace_back(0, 0, 0);


	auto world = getWorld();

	const auto particles = estimator.getParticles();

	float maxValue = std::numeric_limits<float>::lowest();
	float minValue = std::numeric_limits<float>::max();

	for (auto p : particles) {
		const auto v = p->getDensity();
		maxValue = std::max(maxValue, v);
		minValue = std::min(minValue, v);
	}
	std::cout << minValue << std::endl;
	std::cout << maxValue << std::endl;

	auto asScene = new SPHAnisotropicParticleScene(getWorld()->getNextSceneId(), "Vol");
	for (auto p : particles) {
		asScene->addParticle(p);
	}
	auto presenter = asScene->getPresenter();

	auto colorMap = this->colorMapView.getValue();
	colorMap.setMinMax(minValue, maxValue);
	static_cast<SPHAnisotropicParticleScenePresenter*>(presenter)->setColorMap(colorMap);

	presenter->createView(world->getRenderer());

	getWorld()->getScenes()->addScene(asScene);
	*/
}