#include "ZOrderSearchView.h"

#include "../CrystalSpace/ZIndexedSearchAlgo.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

ZOrderSearchView::ZOrderSearchView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	searchRadius("SearchRadius", 1.0)
{
	add(&searchRadius);
}

void ZOrderSearchView::onOk()
{
	ParticleSystem<void*> ps;
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			for (int k = 0; k < 100; ++k) {
				ps.add(Vector3dd(i, j, k), nullptr);
			}
		}
	}

	ZIndexedSearchAlgo algo(searchRadius.getValue(), ps.getBoundingBox().getMin());
	const auto particles = ps.getIParticles();
	for (auto p : particles) {
		algo.add(p->getPosition());
	}
	algo.sort();
	for (auto p : particles) {
		algo.findNeighbors(p->getPosition());
	}
	std::cout << "Search Completed" << std::endl;
}

