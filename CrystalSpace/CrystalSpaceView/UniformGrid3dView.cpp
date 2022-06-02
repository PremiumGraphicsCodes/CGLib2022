#include "UniformGrid3dView.h"

#include "../CrystalSpace/UniformGrid3d.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

UniformGrid3dView::UniformGrid3dView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	searchRadius("SearchRadius", 1.0)
{
	add(&searchRadius);
}

void UniformGrid3dView::onOk()
{
	ParticleSystem<void*> ps;
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			for (int k = 0; k < 100; ++k) {
				ps.add(Vector3dd(i, j, k), nullptr);
			}
		}
	}

	UniformGrid3d grid(searchRadius.getValue(), ps.getBoundingBox().getMin());
	const auto particles = ps.getIParticles();
	for (auto p : particles) {
		grid.add(p);
	}
	auto func = [](IParticle* lhs, IParticle* rhs) {
		return;
	};
	for (auto p : particles) {
		grid.solveInteractions(p, func);
	}
	std::cout << "Search Completed" << std::endl;
}

