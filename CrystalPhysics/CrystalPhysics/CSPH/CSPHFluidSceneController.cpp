#include "CSPHFluidSceneController.h"

#include "CSPHFluidScene.h"
#include "CSPHParticle.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

CSPHFluidSceneController::CSPHFluidSceneController(CSPHFluidScene* model) :
	model(model),
	view(nullptr)
{}

void CSPHFluidSceneController::createView(SceneShader* sceneShader)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getPointShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void CSPHFluidSceneController::updateView()
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