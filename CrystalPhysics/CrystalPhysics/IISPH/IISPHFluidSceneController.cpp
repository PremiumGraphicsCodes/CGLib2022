#include "IISPHFluidSceneController.h"

#include "IISPHFluidScene.h"
#include "IISPHParticle.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

IISPHFluidSceneController::IISPHFluidSceneController(IISPHFluidScene* model) :
	model(model),
	view(nullptr)
{}

void IISPHFluidSceneController::createView(SceneShader* sceneShader)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getPointShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void IISPHFluidSceneController::updateView()
{
	const auto& ps = model->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), glm::vec4(1, 1, 1, 1), 50.0);
		/*
		const auto& pts = p->getPoints();
		for (auto pp : pts) {
			pb.add(pp->getPosition(), glm::vec4(1, 1, 1, 1), 2.0);
		}
		*/
	}
	pb.setMatrix(Math::Matrix4dd());
	this->view->send(pb);

}