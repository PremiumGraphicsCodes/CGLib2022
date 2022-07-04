#include "SPHDensityEstimatorView.h"

#include "../CrystalPhysics/SurfaceConstruction/SPHVolumeConverter.h"

#include "Crystal/Math/Sphere3d.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::Physics;


SPHDensityEstimatorView::SPHDensityEstimatorView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	particleRadiusView("ParticleRadius", 1.0f),
	colorMapView("ColorMap")
{
	add(&particleRadiusView);
	add(&colorMapView);
}

void SPHDensityEstimatorView::onOk()
{
	std::vector<std::unique_ptr<SPHAnisotropicParticle>> particles;

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
					auto ap = std::make_unique<SPHAnisotropicParticle>(p, 1.0f);
				}
			}
		}
	}
	//positions.emplace_back(0, 0, 0);

	//Crystal::IO::PCDBinaryFileReader reader;
	//reader.read("C://Dev//cgstudio4//Blender//CrystalPython//tmp_txt/macro1.pcd");
	//positions = reader.getPCD().data.positions;

	/*
	auto world = getWorld();

	SPHVolumeConverter builder;
	auto sp = builder.buildIsotoropic(positions, particleRadiusView.getValue(), cellLengthView.getValue());
	//auto sp = builder.buildAnisotoropic(positions, particleRadiusView.getValue(), cellLengthView.getValue());

	//auto volumes = builder.getVolumes();
	const auto nodes = sp->getNodes();
	float maxValue = std::numeric_limits<float>::lowest();
	float minValue = std::numeric_limits<float>::max();
	for (auto n : nodes) {
		maxValue = std::max(maxValue, n->getValue());
		minValue = std::min(minValue, n->getValue());
	}
	std::cout << minValue << std::endl;
	std::cout << maxValue << std::endl;

	SparseVolumeScene* svScene = new SparseVolumeScene(getWorld()->getNextSceneId(), "Vol", std::move(sp));
	auto presenter = svScene->getPresenter();

	auto colorMap = this->colorMapView.getValue();
	colorMap.setMinMax(minValue, maxValue);
	static_cast<SparseVolumePresenter*>(presenter)->setColorMap(colorMap);
	presenter->createView(world->getRenderer());

	getWorld()->getScenes()->addScene(svScene);
	*/
}