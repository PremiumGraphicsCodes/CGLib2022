#include "PositionSelectView.h"

#include "PickUICtrl.h"
#include "CameraUICtrl.h"

#include "../Command/GetCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PositionSelectView::PositionSelectView(const std::string& name, World* model, Canvas* canvas) :
	IView(name),
	positionView("Position", Math::Vector3dd(0, 0, 0)),
	button("Pick"),
	world(model),
	canvas(canvas)
{
	add(&positionView);
	add(&button);

	button.setFunction([=](){
		auto ctrl = new PickUICtrl(world, canvas, SceneTypeLabels::PolygonMeshScene, 0.01f);
		//model->getObjects()->getParticleSystems()->findParticleById();
		auto func = [=](int parentId, int childId) {
			/*
			auto particle = model->getObjects()->getParticleSystems()->findParticleById(parentId, childId);
			if (particle != nullptr) {
				this->position = particle->getPosition();
			}
			*/
		};
		ctrl->setFunction(func);
		canvas->setUICtrl(ctrl);
		}
	);
}