#include "TexturePresenter.h"

#include "TextureScene.h"
#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

TexturePresenter::TexturePresenter(TextureScene* model) :
	model(model),
	view(nullptr),
	index(0)
{
}

void TexturePresenter::createView(SceneShader* sceneShader)
{
	this->view = sceneShader->getObjectRenderer()->getMateialScene();
	this->index = this->view->getTextures().size();

	auto texture = sceneShader->getGLFactory()->createTextureObject();
	this->view->add(texture);

	updateView();
}

void TexturePresenter::removeView(SceneShader* sceneShader)
{
	/*
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
	*/
}

void TexturePresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void TexturePresenter::updateScreenView()
{
	auto textures = this->view->getTextures();
	textures[index]->send(*model->getImage());
	this->view->updateTexture(index);
}

void TexturePresenter::updateParentIdView()
{
}

void TexturePresenter::updateChildIdView()
{
}