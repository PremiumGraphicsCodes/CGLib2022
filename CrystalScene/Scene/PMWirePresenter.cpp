#include "PMWirePresenter.h"

#include "PolygonMeshScene.h"

#include "SceneShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;

PMWirePresenter::PMWirePresenter(PolygonMeshScene* model) :
	IPMPresenter(model),
	view(nullptr)
{
}

void PMWirePresenter::createView(SceneShader* sceneShader)
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

void PMWirePresenter::removeView(SceneShader* sceneShader)
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

void PMWirePresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void PMWirePresenter::updateScreenView()
{
	const auto& shape = model->getShape();
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();

	auto faces = shape->getFaces();

	LineBuffer buffer;
	for (const auto& p : ps) {
		buffer.addVertex(p, ColorRGBAf(1.0, 1.0, 1.0, 1.0));
	}

		int materialId = 0;
	//	auto faces = shape->getFaces();
		for (const auto& f : faces) {
			const auto& vIds = f.getVertexIds();
			for (auto index = 0; index < vIds.size()-1; ++index) {
				auto vIndex = vs[vIds[index]];
				auto vNext = vs[vIds[index+1]];
				buffer.addIndex(vIndex.positionId);
				buffer.addIndex(vNext.positionId);
			}
			{
				auto vIndex = vs[vIds.back()];
				auto vNext = vs[vIds.front()];
				buffer.addIndex(vIndex.positionId);
				buffer.addIndex(vNext.positionId);

			}
			/*
			for (const auto vId : vIds) {
				auto vIndex = vs[vId];
				buffer.addIndex(vIndex.positionId);
			}
			*/
		}
	this->view->send(buffer);
}

void PMWirePresenter::updateParentIdView()
{

}

void PMWirePresenter::updateChildIdView()
{

}
