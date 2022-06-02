#include "SPHFlameSimulationView.h"

#include "CrystalScene/Command/Command.h"

#include "../CrystalPhysics/SPHConstant.h"

using namespace Crystal::Math;
//using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;
using namespace Crystal::Physics;

namespace {
	SPHConstant sphConstant;
	SPHFlameConstant flameConstant;

	constexpr auto Uniform = "Uniform";
	constexpr auto Temperature = "Temperature";
	constexpr auto Fuel = "Fuel";
}

SPHFlameSimulationView::SPHFlameSimulationView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	startButton("Start"),
	resetButton("Reset"),
	//	nextButton("Next"),
	timeStepView("TimeStep", 0.01f),
	pressureCoeView("PressureCoe", 1.0f),
	viscosityView("Viscosity", 1.0f),
	densityView("Density", 10.0f),
	boundaryView("Boundary"),
	presenterView("Presenter")
{
	boundaryView.setValue(Box3d(Vector3dd(-20, 0, -20), Vector3dd(20, 20, 20)));
	resetButton.setFunction([=]() { onReset(); });
	add(&resetButton);
	add(&timeStepView);
	add(&pressureCoeView);
	add(&viscosityView);
	add(&densityView);
	add(&boundaryView);
	add(&presenterView);

	presenterView.add(::Uniform);
	presenterView.add(::Temperature);
	presenterView.add(::Fuel);

	presenterView.setSelected(::Uniform);
}

void SPHFlameSimulationView::onOk()
{
	auto world = getWorld();

	flame = new SPHFlameScene(getWorld()->getNextSceneId(), "Flame");
	world->getScenes()->addScene(flame);

	heatSource = new SPHFlameScene(getWorld()->getNextSceneId(), "HeatSource");
	world->getScenes()->addScene(heatSource);

	solver = new SPHFlameSolver();
	solver->add(flame);
	solver->add(heatSource);

	flame->getPresenter()->createView(world->getRenderer());
	heatSource->getPresenter()->createView(world->getRenderer());

	this->onReset();

	//Crystal::Command::Command command;
	//command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	//command.execute(getWorld());

	getWorld()->addAnimation(solver);
}

void SPHFlameSimulationView::onReset()
{
	auto world = getWorld();

	this->flame->clearParticles();
	this->heatSource->clearParticles();
	//this->flame->getPresenter()->removeView(world->getRenderer(), *world->getGLFactory());

	std::unique_ptr<SPHFlameScenePresenter> presenter = std::make_unique<SPHFlameScenePresenter>(this->flame);
	const auto presenterName = presenterView.getSelected();
	if (presenterName == ::Uniform) {
		presenter->setMode(SPHFlameScenePresenter::Mode::Uniform);
	}
	else if (presenterName == ::Temperature) {
		presenter->setMode(SPHFlameScenePresenter::Mode::Temperature);
	}
	else if (presenterName == ::Fuel) {
		presenter->setMode(SPHFlameScenePresenter::Mode::Fuel);
	}
	else {
		assert(false);
	}
	presenter->createView(world->getRenderer());
	this->flame->setPresenter(std::move(presenter));

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	::sphConstant.pressureCoe = pressureCoeView.getValue();
	::sphConstant.viscosityCoe = viscosityView.getValue();
	::sphConstant.effectLength = (length * 1.25);
	solver->setEffectLenth(::sphConstant.effectLength);
	::sphConstant.density = densityView.getValue();
	solver->setTimeStep(timeStepView.getValue());
	solver->setBoundary(boundaryView.getValue());

	flameConstant.k_fd = 1.0e-1f;//1.0e-3f;// 1.0f - 12;
	flameConstant.k_hd = 1.0e-1f;
	flameConstant.k_rs = 1.0e-3f;
	flameConstant.k_buo = 1.0e-1f;//1.0e-12f;
	solver->setExternalForce(Vector3df(0.0, -9.8, 0.0));

	for (int i = -10; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = -10; k < 10; ++k) {
				auto mp = new SPHFlameParticle(Vector3dd(i * length, j * length, k * length), radius, &sphConstant, &flameConstant);
				mp->setFuel(0.1f);
				mp->setTemperature(300.0f);
				mp->setStatic(false);
				flame->addParticle(mp);
			}
		}
	}

	for (int i = -5; i < 5; ++i) {
		for (int j = 1; j < 2; ++j) {
			for (int k = -5; k < 5; ++k) {
				auto mp = new SPHFlameParticle(Vector3dd(i * length, -j * length, k * length), radius, &sphConstant, &flameConstant);
				mp->setStatic(true);
				mp->setFuel(1.0f);
				mp->setTemperature(2000.0f);
				this->heatSource->addParticle(mp);
			}
		}
	}
}
