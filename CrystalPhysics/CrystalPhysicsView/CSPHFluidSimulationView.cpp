#include "CSPHFluidSimulationView.h"

#include "../CrystalPhysics/SPHConstant.h"

using namespace Crystal::Math;
//using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

namespace {
	SPHConstant sphConstant;
}

CSPHFluidSimulationView::CSPHFluidSimulationView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	startButton("Start"),
	resetButton("Reset"),
//	nextButton("Next"),
	timeStepView("TimeStep", 0.001f),
	pressureCoeView("PressureCoe", 1.0f),
	viscosityView("Viscosity", 1.0f),
	densityView("Density", 10.0f),
	boundaryView("Boundary"),
	outputDirectoryView("OutDir"),
	newId(-1)
{
	/*
	auto func = [=]() {
		simulator.simulate(0.01);
		Command::Command command;
		command.create(ShaderSendLabels::CommandNameLabel);
		command.setArg(ShaderSendLabels::IdLabel, newId);
		command.execute(getWorld());
	};
	nextButton.setFunction(func);
	add(&nextButton);
	*/

	boundaryView.setValue(Box3d(Vector3dd(-100, 0, -100), Vector3dd(100, 1000, 100)));
	resetButton.setFunction([=]() { onReset(); } );
	add(&resetButton);
	add(&timeStepView);
	add(&pressureCoeView);
	add(&viscosityView);
	add(&densityView);
	add(&boundaryView);
	add(&outputDirectoryView);
}

void CSPHFluidSimulationView::onOk()
{
	auto world = getWorld();

	fluidScene = new CSPHFluidScene(getWorld()->getNextSceneId(), "Fluid");
	getWorld()->getScenes()->addScene(fluidScene);


	this->newId = fluidScene->getId();

	fluidScene->getPresenter()->createView(getWorld()->getRenderer());

	simulator = new CSPHSolver();
	simulator->add(fluidScene);

	this->onReset();

	//command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	//command.execute(getWorld());


	getWorld()->addAnimation(simulator);

}

void CSPHFluidSimulationView::onReset()
{
	this->fluidScene->clearParticles();

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	::sphConstant.pressureCoe = pressureCoeView.getValue();
	::sphConstant.viscosityCoe = viscosityView.getValue();
	::sphConstant.effectLength = (length * 1.25);
	simulator->setEffectLenth(::sphConstant.effectLength);
	::sphConstant.density = densityView.getValue();
	simulator->setTimeStep(timeStepView.getValue());
	simulator->setBoundary(boundaryView.getValue());
	simulator->setExternalForce(Vector3df(0.0, -9.8, 0.0));

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < 10; ++k) {
				auto mp = new CSPHParticle(Vector3dd(i * length, j * length, k * length), radius, &sphConstant);
				fluidScene->addParticle(mp);
			}
		}
	}
}
