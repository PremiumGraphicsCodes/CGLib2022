#include "MaterialPresenter.h"

#include "MaterialScene.h"
#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

MaterialPresenter::MaterialPresenter(MaterialScene* model) :
	model(model),
	view(nullptr),
	index(0)
{
}

void MaterialPresenter::createView(SceneShader* sceneShader)
{
	this->view = sceneShader->getObjectRenderer()->getMateialScene();
	this->index = this->view->getMaterials().size();
	this->view->add(*this->model->getMaterial());
}

void MaterialPresenter::removeView(SceneShader* sceneShader)
{
	/*
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
	*/
}

void MaterialPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void MaterialPresenter::updateScreenView()
{
	this->view->updateMaterial(index);
}

void MaterialPresenter::updateParentIdView()
{
}

void MaterialPresenter::updateChildIdView()
{
}