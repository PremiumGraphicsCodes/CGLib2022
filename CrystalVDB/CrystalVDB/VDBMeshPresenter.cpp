#include "VDBMeshPresenter.h"

#include "VDBMeshScene.h"

#include "../../CrystalScene/Scene/SceneShader.h"
#include "../../CrystalScene/Scene/LineShaderScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;
using namespace Crystal::VDB;

VDBMeshPresenter::VDBMeshPresenter(VDBMeshScene* model) :
	model(model),
	view(nullptr)
{
}

void VDBMeshPresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new LineShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getWireShader());
		this->view->build(*sceneShader->getGLFactory());

		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	updateView();
}

void VDBMeshPresenter::removeView(SceneShader* sceneShader)
{
	this->view->release(*sceneShader->getGLFactory());
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
}

void VDBMeshPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void VDBMeshPresenter::updateScreenView()
{
	const auto ps = model->getVerticesf();
	LineBuffer buffer;
	for (const auto& p : ps) {
		buffer.addVertex(p, ColorRGBAf(1.0, 1.0, 1.0, 1.0));
	}

	const auto triangles = model->getTriangleFaces();

	for (const auto& tt : triangles) {
		const auto t = tt.indices;
		buffer.addIndex(t[0]);
		buffer.addIndex(t[1]);
		buffer.addIndex(t[1]);
		buffer.addIndex(t[2]);
	}

	const auto quads = model->getQuadFaces();

	for (const auto& qq : quads) {
		const auto q = qq.indices;
		buffer.addIndex(q[0]);
		buffer.addIndex(q[1]);
		buffer.addIndex(q[1]);
		buffer.addIndex(q[2]);
		buffer.addIndex(q[2]);
		buffer.addIndex(q[3]);
	}

	this->view->send(buffer);
}

void VDBMeshPresenter::updateParentIdView()
{
}

void VDBMeshPresenter::updateChildIdView()
{

}
