#include "SPHAnisotropicParticleWirePresenter.h"

//#include "PolygonMeshScene.h"
#include "SurfaceConstruction/SPHAnisotropicParticle.h"
#include "SPHAnisotropicParticleScene.h"

#include "CrystalScene/Scene/SceneShader.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;
using namespace Crystal::Physics;

SPHAnisotropicParticleWirePresenter::SPHAnisotropicParticleWirePresenter(SPHAnisotropicParticleScene* model) :
	ISPHAnisotropicParticlePresenter(model),
	model(model)
{}

void SPHAnisotropicParticleWirePresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new LineShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getWireShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	updateView();

}

void SPHAnisotropicParticleWirePresenter::removeView(SceneShader* sceneShader)
{
	this->view->release(*sceneShader->getGLFactory());
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
}

void SPHAnisotropicParticleWirePresenter::updateView()
{
	LineBuffer buffer;

	int index = 0;

	const auto particles = model->getParticles();
	for (auto p : particles) {
		const auto pos = p->getPosition();
		const auto m = p->getMatrix();
		const auto r = (double)p->getRadius();
		const auto u = m[0] * r;
		const auto v = m[1] * r;
		const auto w = m[2] * r;
		buffer.addVertex(pos, ColorRGBAf(1, 0, 0, 0));
		buffer.addVertex(pos + u, ColorRGBAf(1, 0, 0, 0));

		buffer.addIndex(index);
		buffer.addIndex(index + 1);
		index += 2;

		buffer.addVertex(pos, ColorRGBAf(0, 1, 0, 0));
		buffer.addVertex(pos + v, ColorRGBAf(0, 1, 0, 0));

		buffer.addIndex(index);
		buffer.addIndex(index + 1);
		index += 2;

		buffer.addVertex(pos, ColorRGBAf(0, 0, 1, 0));
		buffer.addVertex(pos + w, ColorRGBAf(0, 0, 1, 0));

		buffer.addIndex(index);
		buffer.addIndex(index + 1);
		index += 2;

	}
	this->view->send(buffer);
}
