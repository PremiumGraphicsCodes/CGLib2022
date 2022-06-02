#include "PMSmoothPresenter.h"

#include "PolygonMeshScene.h"
#include "TriangleShaderScene.h"

#include "SceneShader.h"
#include "SmoothShaderScene.h"

#include "Crystal/Graphics/DrawableId.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;

PMSmoothPresenter::PMSmoothPresenter(PolygonMeshScene* model) : 
	IPMPresenter(model),
	view(nullptr),
	parentIdView(nullptr)
{
}

void PMSmoothPresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new SmoothShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getSmoothShader());
		this->view->build(*sceneShader->getGLFactory());

		/*
		this->view->setMaterialBuffer(sceneShader->getObjectRenderer()->getMateialScene());
		this->view->sendAllMaterials();
		this->view->sendAllLights();
		this->view->sendAllTextures();
		*/

		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	/**
	{
		this->parentIdView = new TriangleShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getObjectRenderer()->getTriangleShader());
		this->parentIdView->build(glFactory);
		sceneShader->getParentIdRenderer()->addScene(this->parentIdView);
	}
	*/

	updateView();
}

void PMSmoothPresenter::removeView(SceneShader* sceneShader)
{
	this->view->release(*sceneShader->getGLFactory());
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;

	this->parentIdView->release(*sceneShader->getGLFactory());
	sceneShader->getParentIdRenderer()->removeScene(this->parentIdView);
	delete this->parentIdView;
}

void PMSmoothPresenter::updateView()
{
	updateScreenView();
	//updateParentIdView();
	//updateChildIdView();
}

void PMSmoothPresenter::updateScreenView()
{
	if (!model->isVisible()) {
		this->view->send(SmoothBuffer());
		return;
	}
	const auto& shape = model->getShape();
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();

	SmoothBuffer buffer;
	auto groups = model->getGroups();

	for (const auto& f : shape->getFaces()) {
		const auto vIds = f.getVertexIds();
		for (const auto vId : vIds) {
			const auto& v = vs[vId];
			const auto& p = ps[v.positionId];
			const auto& n = ns[v.normalId];
			Math::Vector2df texCoord(0, 0);
			if (v.texCoordId != -1) {
				texCoord = tcs[v.texCoordId];
			}
			buffer.addVertex(p, n, texCoord);
		}
	}

	for (const auto& g : groups) {
		const auto& faces = g.faces;
		SmoothGroupBuffer groupBuffer;
		groupBuffer.material = *g.material->getMaterial();
		for (const auto& f : g.faces) {
			const auto vIds = f.getVertexIds();
			for (const auto vId : vIds) {
				groupBuffer.indices.add( vId );
			}
		}
		buffer.addGroup(groupBuffer);
	}
	this->view->send(buffer);
}

void PMSmoothPresenter::updateParentIdView()
{
	const auto objectId = model->getId();
	const auto& vertices = model->getShape()->getVertices();
	const auto& positions = model->getShape()->getPositions();
	const auto& faces = model->getShape()->getFaces();
	int childId = 0;
	int index = 0;

	TriangleBuffer buffer;
	//buffer.setMatrix(scene->getMatrix());
	for (auto f : faces) {
		Graphics::DrawableID parentDid(objectId);
		Graphics::DrawableID childDid(childId++);
		const auto& idColor = parentDid.toColor();
		const auto& vIds = f.getVertexIds();

		buffer.addVertex(positions[vertices[vIds[0]].positionId], idColor);
		buffer.addVertex(positions[vertices[vIds[1]].positionId], idColor);
		buffer.addVertex(positions[vertices[vIds[2]].positionId], idColor);
		buffer.addIndex(index++);
		buffer.addIndex(index++);
		buffer.addIndex(index++);
	}
	parentIdView->send(buffer);
}

void PMSmoothPresenter::updateChildIdView()
{

}
