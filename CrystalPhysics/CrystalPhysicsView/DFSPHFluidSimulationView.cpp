#include "DFSPHFluidSimulationView.h"

#include "../CrystalPhysics/DFSPH/DFFluidScene.h"
#include "../CrystalPhysics/DFSPH/DFFluidSolver.h"
#include "../CrystalPhysics/DFSPH/DFSPHParticle.h"
#include "../CrystalPhysics/SPHConstant.h"

#include "CrystalScene/Command/Command.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;
using namespace Crystal::Physics;

namespace {
	SPHConstant sphConstant(1.0f, 1000.0f, 0.0f, 0.0f, 2.25f);
	SPHKernel sphKernel;
	//sphConstant.
}

DFSPHFluidSimulationView::DFSPHFluidSimulationView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	startButton("Start"),
	resetButton("Reset"),
	timeStepView("TimeStep", 0.01f),
	viscosityCoeView("ViscosityCoe", 1000.0f),
	boundaryView("Boundary")
{

	auto resetFunc = [=]() {
		reset();
	};
	resetButton.setFunction(resetFunc);
	add(&resetButton);

	boundaryView.setValue(Box3d(Vector3dd(0, 0.0, 0.0), Vector3dd(100.0, 1000.0, 50.0)));
	
	add(&viscosityCoeView);
	add(&timeStepView);
	add(&boundaryView);
}

void DFSPHFluidSimulationView::onOk()
{
	auto world = getWorld();

	this->fluidScene = new DFFluidScene(getWorld()->getNextSceneId(), "DFFluid");
	this->simulator = new DFFluidSolver();


	reset();
	getWorld()->getScenes()->addScene(this->fluidScene);
	this->newId = this->fluidScene->getId();

	fluidScene->getPresenter()->createView(getWorld()->getRenderer());


	updater.add(fluidScene);

	//boundaryScene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());


	//command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	//command.execute(getWorld());


	simulator->add(this->fluidScene);


	simulator->setExternalForce(Vector3df(0.0, -9.8, 0.0));

	getWorld()->addAnimation(simulator);
	getWorld()->addAnimation(&updater);
}

void DFSPHFluidSimulationView::reset()
{
	//this->simulator->clear();
	this->fluidScene->clearParticles();

	//auto mp = new DFSPHParticle(Vector3dd(0,0,0), 1.0, &sphConstant, &sphKernel);
	//this->fluidScene->addParticle(mp);

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new DFSPHParticle(Vector3dd(i * length, j * length, k * length), radius, &sphConstant, &sphKernel);
				this->fluidScene->addParticle(mp);
			}
		}
	}
	sphConstant.viscosityCoe = viscosityCoeView.getValue();
	simulator->setBoundary(boundaryView.getValue());
	simulator->setTimeStep(timeStepView.getValue());
}
