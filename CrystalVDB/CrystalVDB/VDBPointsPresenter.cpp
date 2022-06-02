#include "VDBPointsPresenter.h"

#include "VDBPointsScene.h"

#include "../../CrystalScene/Scene/SceneShader.h"
#include "../../CrystalScene/Scene/PointShaderScene.h"
#include "VDBPointsImpl.h"
#include "Converter.h"
//#include "PointShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
using namespace Crystal::VDB;

VDBPointsPresenter::VDBPointsPresenter(VDBPointsScene* model) :
	IPresenter(),
	model(model),
	view(nullptr),
	parentIdView(nullptr),
	childIdView(nullptr)
{
}

void VDBPointsPresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getPointShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	/*
	{
		this->parentIdView = new PointShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->parentIdView->build(glFactory);
		sceneShader->getParentIdRenderer()->addScene(this->parentIdView);
	}

	{
		this->childIdView = new PointShaderScene(model->getName());
		this->childIdView->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->childIdView->build(glFactory);
		sceneShader->getChildIdRenderer()->addScene(this->childIdView);
	}
	*/
	updateView();
}

void VDBPointsPresenter::removeView(SceneShader* sceneShader)
{
	this->view->release(*sceneShader->getGLFactory());
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;

	/*
	this->parentIdView->release(factory);
	sceneShader->getParentIdRenderer()->removeScene(this->parentIdView);
	delete this->parentIdView;

	this->childIdView->release(factory);
	sceneShader->getParentIdRenderer()->removeScene(this->childIdView);
	delete this->childIdView;
	*/
}

void VDBPointsPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void VDBPointsPresenter::updateScreenView()
{
	auto impl = model->getImpl();
	const auto size = impl->size();// getShape()->getParticles();
	PointBuffer pb;
	const auto positions = model->getPositions();
	for (int i = 0; i < size; ++i) {
		pb.add(positions[i], ColorRGBAf(1,1,1,1), 1.0f);
	}

	this->view->send(pb);
	this->view->setVisible(model->isVisible());
}

void VDBPointsPresenter::updateParentIdView()
{
}

void VDBPointsPresenter::updateChildIdView()
{
}