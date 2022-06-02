#include "LightPresenter.h"

#include "MaterialScene.h"
#include "SceneShader.h"

#include "LightScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

LightPresenter::LightPresenter(LightScene* model) :
	model(model),
	view(nullptr),
	index(0)
{
}

void LightPresenter::createView(SceneShader* sceneShader)
{
	this->view = sceneShader->getObjectRenderer()->getMateialScene();
	this->index = static_cast<int>( this->view->getLights().size() );
	this->view->add(*this->model->getLight());
}

void LightPresenter::removeView(SceneShader* sceneShader)
{
	/*
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
	*/
}

void LightPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void LightPresenter::updateScreenView()
{
	this->view->updateLight(index);
}

void LightPresenter::updateParentIdView()
{
}

void LightPresenter::updateChildIdView()
{
}