#include "VDBVolumePresenter.h"

#include "VDBVolumeScene.h"

#include "VDBVolumeImpl.h"
#include "Converter.h"

#include "../../CrystalScene/Scene/SceneShader.h"
#include "../../CrystalScene/Scene/PointShaderScene.h"
//#include "PointShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
using namespace Crystal::VDB;

VDBVolumePresenter::VDBVolumePresenter(VDBVolumeScene* model) :
	IPresenter(),
	model(model),
	view(nullptr)
{
	this->colorMap = ColorMap(0.0, 1.0, ColorTable::createDefaultTable(270));
}

void VDBVolumePresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getPointShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void VDBVolumePresenter::removeView(SceneShader* sceneShader)
{
	this->view->release(*sceneShader->getGLFactory());
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
}

void VDBVolumePresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void VDBVolumePresenter::updateScreenView()
{
	auto impl = model->getImpl();
	auto grid = impl->getPtr();
	auto transform = grid->transform();
	PointBuffer pb;
	for (auto iter = grid->cbeginValueOn(); iter; ++iter) {
		//auto c = iter.getCoord();
		auto coord = transform.indexToWorld(iter.getCoord());
		auto value = *iter;
		const auto c = colorMap.getColor((float)value);
		pb.add(Converter::fromVDB(coord), c, 1.0f);
	}
	this->view->send(pb);
	this->view->setVisible(true);
	//this->view->send(pb);
}

void VDBVolumePresenter::updateParentIdView()
{
}

void VDBVolumePresenter::updateChildIdView()
{
}