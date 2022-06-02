#include "ParticleSystemPresenter.h"

#include "ParticleSystemScene.h"
#include "SceneShader.h"
#include "PointShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

ParticleSystemPresenter::ParticleSystemPresenter(ParticleSystemScene* model) :
	IParticleSystemPresenter(model),
	view(nullptr),
	parentIdView(nullptr),
	childIdView(nullptr),
	doBlend(false)
{
}

void ParticleSystemPresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getPointShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	{
		this->parentIdView = new PointShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getRenderers()->getPointShader());
		this->parentIdView->build(*sceneShader->getGLFactory());
		sceneShader->getParentIdRenderer()->addScene(this->parentIdView);
	}

	{
		this->childIdView = new PointShaderScene(model->getName());
		this->childIdView->setShader(sceneShader->getRenderers()->getPointShader());
		this->childIdView->build(*sceneShader->getGLFactory());
		sceneShader->getChildIdRenderer()->addScene(this->childIdView);
	}
	updateView();
}

void ParticleSystemPresenter::removeView(SceneShader* sceneShader)
{
	this->view->release(*sceneShader->getGLFactory());
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;

	this->parentIdView->release(*sceneShader->getGLFactory());
	sceneShader->getParentIdRenderer()->removeScene(this->parentIdView);
	delete this->parentIdView;

	this->childIdView->release(*sceneShader->getGLFactory());
	sceneShader->getParentIdRenderer()->removeScene(this->childIdView);
	delete this->childIdView;
}

void ParticleSystemPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void ParticleSystemPresenter::updateScreenView()
{
	const auto& ps = model->getShape()->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}

	this->view->setBlend(this->doBlend);
	this->view->send(pb);
	this->view->setVisible(model->isVisible());
}

void ParticleSystemPresenter::updateParentIdView()
{
	const auto objectId = model->getId();
	const auto& particles = model->getShape()->getParticles();
	int particleId = 0;
	PointBuffer parentIdBuffer;
	for (auto p : particles) {
		DrawableID parentDid(objectId);
		parentIdBuffer.add(p->getPosition(), parentDid.toColor(), p->getAttribute().size);
	}
	parentIdView->send(parentIdBuffer);
	parentIdView->setVisible(model->isVisible());
}

void ParticleSystemPresenter::updateChildIdView()
{
	const auto objectId = model->getId();
	const auto& particles = model->getShape()->getParticles();
	int particleId = 0;
	PointBuffer buffer;
	for (auto p : particles) {
		DrawableID childDid(particleId++);
		buffer.add(p->getPosition(), childDid.toColor(), p->getAttribute().size);
	}
	childIdView->send(buffer);
	childIdView->setVisible(model->isVisible());
}