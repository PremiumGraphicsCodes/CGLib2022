#include "MVPFluidScenePresenter.h"

#include "MVPFluidScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

MVPFluidScenePresenter::MVPFluidScenePresenter(IMVPFluidScene* model) :
	IMVPFluidScenePresenter(model),
	model(model),
	view(nullptr),
	mode(Mode::Density)
{
	//colorMap = ColorMap(2.0f, 3.0f, ColorTable::createDefaultTable(270));
	colorMap = ColorMap(300.0f, 400.0f, ColorTable::createDefaultTable(270));
}

void MVPFluidScenePresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getPointShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void MVPFluidScenePresenter::updateView()
{
	const auto& ps = model->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		ColorRGBAf c;
		if (mode == Mode::Uniform) {
			c = glm::vec4(1, 1, 1, 0.25);
		}
		else if (mode == Mode::Density) {
			c = colorMap.getInterpolatedColor(p->getTemperature());
			//c = colorMap.getInterpolatedColor(p->getDensity());
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