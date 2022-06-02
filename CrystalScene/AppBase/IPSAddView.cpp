#include "IPSAddView.h"

#include "../Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

IPSAddView::IPSAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	//matrixView("Matrix", Math::Identity()),
	attributeView("PSAttribute"),
	nameView("Name", "ParticleSystem01"),
	presenterView("Presenter"),
	doBlendView("Blend", false)
{
	//add(&matrixView);
	add(&attributeView);
	add(&nameView);
	add(&presenterView);
	add(&doBlendView);
}

void IPSAddView::addParticleSystem(const std::vector<Vector3dd>& positions)
{
	auto attr = attributeView.getValue();
	auto name = nameView.getValue();
	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
	auto scene = new ParticleSystemScene(getWorld()->getNextSceneId(), name, std::move(shape));
	getWorld()->getScenes()->addScene(scene);
	const auto newId = scene->getId();

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer());
}