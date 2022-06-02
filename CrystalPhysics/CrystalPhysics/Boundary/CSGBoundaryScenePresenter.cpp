#include "CSGBoundaryScenePresenter.h"

#include "CSGBoundaryScene.h"

#include "Crystal/Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

CSGBoundaryScenePresenter::CSGBoundaryScenePresenter(CSGBoundaryScene* model) :
	model(model),
	view(nullptr)
{}

void CSGBoundaryScenePresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new LineShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getWireShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void CSGBoundaryScenePresenter::updateView()
{
	const auto& boxes = model->getBoxes();
	
	WireFrameBuilder builder;
	for (const auto& b : boxes) {
		builder.add(b);
	}
	const auto edges = builder.getEdges();
	const auto positions = builder.getPositions();
	LineBuffer buffer;
	for (const auto& l : positions) {
		buffer.addVertex(l, ColorRGBAf(1.0, 1.0, 1.0, 1.0));
	}
	for (const auto& e : edges) {
		buffer.addIndex(e.originId);
		buffer.addIndex(e.destId);
	}
	buffer.setMatrix(Math::Matrix4dd());
	this->view->send(buffer);
}