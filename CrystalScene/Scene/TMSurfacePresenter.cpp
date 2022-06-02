#include "TMSurfacePresenter.h"

#include "TriangleMeshScene.h"
#include "TriangleShaderScene.h"

#include "SceneShader.h"

#include "Crystal/Graphics/DrawableId.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;

TMSurfacePresenter::TMSurfacePresenter(TriangleMeshScene* model) :
	ITMPresenter(model),
	view(nullptr),
	color(0.0, 0.0, 1.0, 0.0)
{
}

void TMSurfacePresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new TriangleShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getTriangleShader());
		this->view->build(*sceneShader->getGLFactory());

		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	updateView();
}

void TMSurfacePresenter::removeView(SceneShader* sceneShader)
{
	this->view->release(*sceneShader->getGLFactory());
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
}

void TMSurfacePresenter::updateView()
{
	updateScreenView();
	//updateParentIdView();
	//updateChildIdView();
}

void TMSurfacePresenter::updateScreenView()
{
//	const auto objectId = model->getId();
	if (model->getShape() == nullptr) {
		return;
	}
	const auto& faces = model->getShape()->getFaces();

	TriangleBuffer buffer;
	int index = 0;
	for (auto f : faces) {
		const auto vs = f.triangle.getVertices();

		buffer.addVertex(vs[0], color);
		buffer.addVertex(vs[1], color);
		buffer.addVertex(vs[2], color);
		buffer.addIndex(index++);
		buffer.addIndex(index++);
		buffer.addIndex(index++);
	}
	view->send(buffer);
}

void TMSurfacePresenter::updateParentIdView()
{
}

void TMSurfacePresenter::updateChildIdView()
{

}
