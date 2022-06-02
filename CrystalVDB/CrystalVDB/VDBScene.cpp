#include "VDBScene.h"

using namespace Crystal::VDB;
using namespace Crystal::Scene;

void VDBScene::add(VDBVolumeScene* volume)
{
	this->volumes.push_back(volume);
	this->children.push_back(volume);
}

void VDBScene::add(VDBPointsScene* points)
{
	this->points.push_back(points);
	this->children.push_back(points);
}

void VDBScene::add(VDBMeshScene* mesh)
{
	this->meshes.push_back(mesh);
	this->children.push_back(mesh);
}

SceneType VDBScene::getType() const
{
	return SceneType("VDBScene");
}

IPresenter* VDBScene::getPresenter()
{
	return nullptr;
}
