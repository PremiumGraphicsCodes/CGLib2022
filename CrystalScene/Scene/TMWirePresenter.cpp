#include "TMWirePresenter.h"

#include "TriangleMeshScene.h"

#include "SceneShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;

TMWirePresenter::TMWirePresenter(TriangleMeshScene* model) :
	ITMPresenter(model),
	view(nullptr)
{
}

void TMWirePresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new LineShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getWireShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	updateView();

}

void TMWirePresenter::removeView(SceneShader* sceneShader)
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

void TMWirePresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void TMWirePresenter::updateScreenView()
{
	const auto& shape = model->getShape();
	const auto faces = shape->getFaces();

	LineBuffer buffer;

	int vertexId = 0;
	for (const auto& f : faces) {
		const auto vs = f.triangle.getVertices();
		for (auto v : vs) {
			buffer.addVertex(v, ColorRGBAf(1.0, 1.0, 1.0, 1.0));
		}
		buffer.addIndex(vertexId);
		buffer.addIndex(vertexId + 1);

		buffer.addIndex(vertexId + 1);
		buffer.addIndex(vertexId + 2);

		buffer.addIndex(vertexId + 2);
		buffer.addIndex(vertexId);

		vertexId += 3;
	}
	this->view->send(buffer);
}

void TMWirePresenter::updateParentIdView()
{

}

void TMWirePresenter::updateChildIdView()
{

}
