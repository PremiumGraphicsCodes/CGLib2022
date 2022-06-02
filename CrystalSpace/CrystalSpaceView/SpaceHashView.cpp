#include "SpaceHashView.h"

#include "../CrystalSpace/SpaceHash3d.h"
#include "../CrystalSpace/StopWatch.h"
#include "../../Crystal/Shape/ParticleSystem.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

SpaceHashView::SpaceHashView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	searchRadius("SearchRadius", 1.0)
{
	add(&searchRadius);
}

void SpaceHashView::onOk()
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

	SpaceHash3d grid(searchRadius.getValue(), 10000000);
	const auto particles = ps.getIParticles();
	for (auto p : particles) {
		grid.add(p);
	}
	unsigned int pairCount = 0;
	auto func = [&pairCount](IParticle* lhs, IParticle* rhs) {
		pairCount++;
	};
	for (auto p : particles) {
		grid.solveInteractions(p, func);
	}
	sw.stop();

	std::cout << "Pairs " << pairCount << std::endl;
	std::cout << "Search Completed " << sw.getElapsed() << "[ms]" << std::endl;
}