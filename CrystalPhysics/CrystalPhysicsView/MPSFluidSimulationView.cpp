#include "MPSFluidSimulationView.h"

using namespace Crystal::Math;
//using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

MPSFluidSimulationView::MPSFluidSimulationView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	startButton("Start"),
	resetButton("Reset"),
	timeStepView("TimeStep", 0.001f),
	pressureCoeView("PressureCoe", 1.0f),
	viscosityView("Viscosity", 1.0f),
	densityView("Density", 10.0f),
	boundaryView("Boundary")
{

	boundaryView.setValue(Box3d(Vector3dd(-100, 0, -100), Vector3dd(100, 1000, 100)));
	resetButton.setFunction([=]() { onReset(); });
	add(&resetButton);
	add(&timeStepView);
	add(&pressureCoeView);
	add(&viscosityView);
	add(&densityView);
	add(&boundaryView);
}

void MPSFluidSimulationView::onOk()
{
	auto world = getWorld();

	fluidScene = new MPSFluidScene(getWorld()->getNextSceneId(), "MPSFluid");
	getWorld()->getScenes()->addScene(fluidScene);

	//this->newId = fluidScene->getId();

	simulator = new MPSFluidSolver();
	//simulator->add(fluidScene);

	this->onReset();

	fluidScene->getPresenter()->createView(getWorld()->getRenderer());

	//command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	//command.execute(getWorld());


	//getWorld()->addAnimation(simulator);

}

void MPSFluidSimulationView::onReset()
{
	this->fluidScene->clearParticles();

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	//simulator->setEffectLenth(::sphConstant.effectLength);
	//simulator->setTimeStep(timeStepView.getValue());
	//simulator->setBoundary(boundaryView.getValue());
	//simulator->setExternalForce(Vector3df(0.0, -9.8, 0.0));

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < 10; ++k) {
				auto p = new MPSParticle(Vector3df(i * length, j * length, k * length));
				fluidScene->addParticle(p);
			}
		}
	}
}
