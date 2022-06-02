#include "PBFluidSceneController.h"

#include "PBFluidScene.h"
#include "PBSPHParticle.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

PBFluidSceneController::PBFluidSceneController(PBFluidScene* model) :
	model(model),
	view(nullptr),
	mode(Mode::Density)
{
	colorMap = ColorMap(2.0f, 3.0f, ColorTable::createDefaultTable(270));
}

void PBFluidSceneController::createView(SceneShader* sceneShader)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getPointShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void PBFluidSceneController::updateView()
{
	const auto& ps = model->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		ColorRGBAf c;
		if (mode == Mode::Uniform) {
			c = glm::vec4(1, 1, 1, 0.25);
		}
		else if (mode == Mode::Density) {
			c = colorMap.getInterpolatedColor(p->getDensity());
		}
		else {
			assert(false);
		}
		pb.add(p->getPosition(), c, 10.0);
		/*
		const auto& pts = p->getPoints();
		for (auto pp : pts) {
			pb.add(pp->getPosition(), glm::vec4(1, 1, 1, 1), 2.0);
		}
		*/
	}
	pb.setMatrix(Math::Matrix4dd());
	//	this->view->setBlend(true);
	this->view->send(pb);

}