#include "IndexedSortSearchAlgoView.h"

#include "../CrystalSpace/IndexedSortSearchAlgo.h"
#include "../CrystalSpace/StopWatch.h"
#include "../../Crystal/Shape/ParticleSystem.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

IndexedSortSearchAlgoView::IndexedSortSearchAlgoView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	searchRadius("SearchRadius", 1.0)
{
	add(&searchRadius);
}

void IndexedSortSearchAlgoView::onOk()
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

	IndexedSortSearchAlgo searchAlgo(searchRadius.getValue());
	const auto particles = ps.getIParticles();
	for (auto p : particles) {
		searchAlgo.add(p);
	}
	searchAlgo.createPairs();
	const auto pairs = searchAlgo.getPairs();
	sw.stop();

	std::cout << "Pairs " << pairs.size() << std::endl;
	std::cout << "Search Completed " << sw.getElapsed() << "[ms]" << std::endl;
}