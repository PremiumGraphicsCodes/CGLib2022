#include "VoxelPresenter.h"

#include "CrystalScene/Scene/PointShaderScene.h"
#include "CrystalScene/Scene/SceneShader.h"
#include "VoxelScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Space;

VoxelPresenter::VoxelPresenter(VoxelScene* model) :
	model(model),
	view(nullptr)
{
}

void VoxelPresenter::createView(SceneShader* sceneShader)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getRenderers()->getPointShader());
		this->view->build(*sceneShader->getGLFactory());
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void VoxelPresenter::removeView(SceneShader* sceneShader)
{
	this->view->release(*sceneShader->getGLFactory());
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
}

void VoxelPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void VoxelPresenter::updateScreenView()
{
	PointBuffer pb;
	auto nodes = model->getShape()->getNodes();

	const auto res = nodes.getResolutions();

	Graphics::ColorRGBAf color(0, 0, 0, 0);
	for (int i = 0; i < res[0]; ++i) {
		for (int j = 0; j < res[1]; ++j) {
			for (int k = 0; k < res[2]; ++k) {
				const auto pos = model->getShape()->getCellPosition(i, j, k);
				const auto value = model->getShape()->getValue(i, j, k);
				if (value) {
					pb.add(pos, color, 50.0f);
				}
			}
		}
	}
	this->view->send(pb);
}

void VoxelPresenter::updateParentIdView()
{
}

void VoxelPresenter::updateChildIdView()
{
}