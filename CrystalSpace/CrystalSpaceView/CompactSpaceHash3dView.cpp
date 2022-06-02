#include "CompactSpaceHash3dView.h"

#include "../CrystalSpace/CompactSpaceHash3d.h"
#include "../CrystalSpace/StopWatch.h"
#include "../../Crystal/Shape/ParticleSystem.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

CompactSpaceHash3dView::CompactSpaceHash3dView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	searchRadius("SearchRadius", 1.0)
{
	add(&searchRadius);
}

void CompactSpaceHash3dView::onOk()
{
	ParticleSystem<void*> ps;
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			for (int k = 0; k < 100; ++k) {
				ps.add(Vector3dd(i, j, k), nullptr);
			}
		}
	}

	Crystal::Space::StopWatch sw;
	sw.start();

	CompactSpaceHash3d spaceHash(searchRadius.getValue(), 10000000);
	const auto particles = ps.getIParticles();
	for (auto p : particles) {
		spaceHash.add(p);
	}
	unsigned int count = 0;
#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		auto p = particles[i];
		const auto& neighbors = spaceHash.findNeighbors(p);
		count += neighbors.size();
	}
	sw.stop();

	std::cout << "Pairs " << count << std::endl;
	std::cout << "Search Completed " << sw.getElapsed() << "[ms]" << std::endl;
}