#include "SPHFlameScenePresenter.h"

#include "SPHFlameScene.h"
#include "SPHFlameParticle.h"

#include "../../../Crystal/Graphics/ColorHSV.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

SPHFlameScenePresenter::SPHFlameScenePresenter(SPHFlameScene* model) :
	model(model),
	view(nullptr),
	mode(Mode::Uniform)
{
	const ColorTable table = ColorTable::createDefaultTable(270);
	colorMap = ColorMap(300.0f, 400.0f, table);
}

void SPHFlameScenePresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getPointShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void SPHFlameScenePresenter::updateView()
{
	const auto& ps = model->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		ColorRGBAf c;
		if (mode == Mode::Uniform) {
			c = glm::vec4(1, 1, 1, 1);
		}
		else if (mode == Mode::Temperature) {
			c = colorMap.getColor(p->getTemperature());
			colorMap.setMinMax(300.0f, 400.0f);
		}
		else if (mode == Mode::Fuel) {
			c = colorMap.getColor(p->getFuel());
			colorMap.setMinMax(0.0f, 1.0f);
		}
		else {
			assert(false);
		}
		pb.add(p->getPosition(), c, 50.0);
		/*
		const auto& pts = p->getPoints();
		for (auto pp : pts) {
			pb.add(pp->getPosition(), , 2.0);
		}
		*/
	}
	pb.setMatrix(Math::Matrix4dd());
	this->view->send(pb);

}