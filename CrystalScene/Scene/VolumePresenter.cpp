#include "VolumePresenter.h"

#include "VolumeScene.h"
#include "PointShaderScene.h"
#include "SceneShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

VolumePresenter::VolumePresenter(VolumeScene* model) :
	model(model),
	view(nullptr)
{
}

void VolumePresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getPointShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void VolumePresenter::removeView(SceneShader* sceneShader)
{
	this->view->release(*sceneShader->getGLFactory());
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
}

void VolumePresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void VolumePresenter::updateScreenView()
{
	PointBuffer pb;
	auto shape = model->getShape();

	const auto& resolutions = shape->getResolutions();
	for (auto ix = 0; ix < resolutions[0]; ix++) {
		for (auto iy = 0; iy < resolutions[1]; iy++) {
			for (auto iz = 0; iz < resolutions[2]; iz++) {
				const auto p = shape->getCellPosition(ix, iy, iz);
				const auto v = shape->getValue(ix, iy, iz);
				const auto c = colorMap.getColor(v);
				pb.add(p, c, 10.0f);
//				shape->get
			}
		}
	}
	this->view->send(pb);
	/*
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	*/
}

void VolumePresenter::updateParentIdView()
{
}

void VolumePresenter::updateChildIdView()
{
}