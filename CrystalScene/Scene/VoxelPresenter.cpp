#include "VoxelPresenter.h"

#include "VoxelScene.h"
#include "PointShaderScene.h"
#include "SceneShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

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
	auto shape = model->getShape();

	const auto& resolutions = shape->getResolutions();
	for (auto ix = 0; ix < resolutions[0]; ix++) {
		for (auto iy = 0; iy < resolutions[1]; iy++) {
			for (auto iz = 0; iz < resolutions[2]; iz++) {
				const auto p = shape->getCellPosition(ix, iy, iz);
				const auto v = shape->getValue(ix, iy, iz);
				if (v) {
					ColorRGBAf c(1.0f, 1.0f, 1.0f, 1.0f);
					pb.add(p, c, 10.0f);
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