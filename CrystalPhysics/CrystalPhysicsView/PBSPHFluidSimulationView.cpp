#include "PBSPHFluidSimulationView.h"

#include "../CrystalPhysics/PBSPH/PBFluidScene.h"
#include "../CrystalPhysics/PBSPH/PBSPHSolver.h"
#include "../CrystalPhysics/PBSPH/PBSPHParticle.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

PBSPHFluidSimulationView::PBSPHFluidSimulationView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	startButton("Start"),
	resetButton("Reset"),
	timeStepView("TimeStep", 0.01f),
	radiusView("Radius", 1.0f),
	effectLengthView("EffectLength", 2.25f),
	densityView("Density", 1.0f),
	boundaryView("Boundary"),
	stiffnessView("Stiffness", 0.05f),
	vicsocityView("Viscosity", 0.1f)
{
	resetButton.setFunction([=]() { onReset(); });
	boundaryView.setValue(Box3d(Vector3dd(0, 0.0, 0.0), Vector3dd(100.0, 1000.0, 40.0)));

	add(&resetButton);
	add(&timeStepView);
	add(&radiusView);
	add(&densityView);
	add(&effectLengthView);
	add(&boundaryView);
	add(&stiffnessView);
	add(&vicsocityView);
}

void PBSPHFluidSimulationView::onOk()
{
	auto world = getWorld();

	this->fluidScene = new PBFluidScene(getWorld()->getNextSceneId(), "Fluid");
	//this->boundaryScene = new PBFluidScene(getWorld()->getNextSceneId(), "Boundary");
	this->simulator = new PBSPHSolver();
	
	onReset();

	getWorld()->getScenes()->addScene(this->fluidScene);
	auto newId = this->fluidScene->getId();
	this->fluidScene->getPresenter()->createView(world->getRenderer());

	//getWorld()->getScenes()->addScene(this->boundaryScene);
	//auto boundaryId = this->boundaryScene->getId();

	//command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	//command.execute(getWorld());

	simulator->add(this->fluidScene);
	//simulator->add(this->boundaryScene);

	simulator->setExternalForce(Vector3df(0.0, -9.8, 0.0));

	getWorld()->addAnimation(simulator);
	//getWorld()->addAnimation(&writer);
}

void PBSPHFluidSimulationView::onReset()
{
	//this->simulator->clear();
	this->fluidScene->clearParticles();
	this->fluidScene->setEffectLength(this->effectLengthView.getValue());
	this->fluidScene->setRestDensity(this->densityView.getValue());
	this->fluidScene->setStiffness(this->stiffnessView.getValue());
	this->fluidScene->setVicsosity(this->vicsocityView.getValue());

	//this->boundaryScene->clearParticles();
	//this->boundaryScene->setEffectLength(this->effectLengthView.getValue());
	//this->boundaryScene->setRestDensity(this->densityView.getValue());
	//this->boundaryScene->setStiffness(this->stiffnessView.getValue() * 10.0f);
	//this->boundaryScene->setVicsosity(this->vicsocityView.getValue());
	//this->boundaryScene->setIsBoundary(true);

	//this->writer.reset();
//	this->writer.setDirectryPath(outputDirectoryView.getPath());


	/*
	const auto& ps = scene->getShape()->getParticles();
	for (auto p : ps) {
		auto pos = p->getPosition();
		auto mp = new PBSPHParticle(pos, radiusView.getValue(), this->fluidScene);
		this->fluidScene->addParticle(mp);
		writer.add(mp);
	}
	*/

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new PBSPHParticle(Vector3dd(i * length, j * length, k * length), radius, this->fluidScene);
				this->fluidScene->addParticle(mp);
			}
		}
	}


	simulator->setBoundary(boundaryView.getValue());
	simulator->setTimeStep(timeStepView.getValue());
}
