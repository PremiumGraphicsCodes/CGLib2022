#include "MeshBoundaryScenePresenter.h"

#include "MeshBoundaryScene.h"

//#include "SceneShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;
using namespace Crystal::Physics;

MeshBoundaryScenePresenter::MeshBoundaryScenePresenter(MeshBoundaryScene* model) :
	model(model),
	view(nullptr)
{
}

void MeshBoundaryScenePresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new LineShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getWireShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	/*
	{
		this->parentIdView = new LineShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getObjectRenderer()->getWireShader());
		this->parentIdView->build(glFactory);
		sceneShader->getScene()->parentId.add(this->parentIdView);
	}
	*/

	updateView();

}

void MeshBoundaryScenePresenter::removeView(SceneShader* sceneShader)
{
	this->view->release(*sceneShader->getGLFactory());
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;

	/*
	this->parentIdView->release(glFactory);
	sceneShader->getParentIdRenderer()->removeScene(this->parentIdView);
	delete this->parentIdView;
	*/
}

void MeshBoundaryScenePresenter::updateView()
{
	updateScreenView();
	//updateParentIdView();
	//updateChildIdView();
}

void MeshBoundaryScenePresenter::updateScreenView()
{
	const auto shape = model->getMesh();
	if (shape == nullptr) {
		return;
	}
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();

	auto faces = shape->getFaces();

	LineBuffer buffer;
	for (const auto& p : ps) {
		buffer.addVertex(p, ColorRGBAf(1.0, 1.0, 1.0, 1.0));
	}

	//auto faces = shape->getFaces();
	for (const auto& f : faces) {
		const auto& vIds = f.getVertexIds();
		for (const auto vId : vIds) {
			auto vIndex = vs[vId];
			buffer.addIndex(vIndex.positionId);
		}
	}
	this->view->send(buffer);
}
