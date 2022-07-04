#include "SPHAnisotropicParticleScenePresenter.h"

#include "SPHAnisotropicParticleScene.h"
#include "SurfaceConstruction/SPHAnisotropicParticle.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

SPHAnisotropicParticleScenePresenter::SPHAnisotropicParticleScenePresenter(SPHAnisotropicParticleScene* model) :
	ISPHAnisotropicParticlePresenter(model),
	model(model),
	view(nullptr)
{
	colorMap = ColorMap(2.0f, 3.0f, ColorTable::createDefaultTable(270));
}

void SPHAnisotropicParticleScenePresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getPointShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void SPHAnisotropicParticleScenePresenter::updateView()
{
	const auto& ps = model->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		const ColorRGBAf c = colorMap.getInterpolatedColor(p->getDensity());
		pb.add(p->getPosition(), c, p->getRadius());
	}
	pb.setMatrix(Math::Matrix4dd());
	//	this->view->setBlend(true);
	this->view->send(pb);

}