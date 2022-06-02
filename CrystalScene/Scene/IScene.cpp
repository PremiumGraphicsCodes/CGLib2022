#include "IScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

IScene::IScene() :
	id(-1),
	_isVisible(false),
	_isPickable(true),
	parent(nullptr)
{}

IScene::IScene(const int id) :
	id(id),
	_isVisible(true),
	_isPickable(true),
	parent(nullptr)
{}

IScene::IScene(const int id, const std::string& name) :
	id(id),
	name(name),
	_isVisible(true),
	_isPickable(true),
	parent(nullptr)
{}

IScene::~IScene()
{
}

void IScene::clear()
{
	for (const auto& c : children) {
		c->clear();
	}
	children.clear();
}

void IScene::addScene(IScene* scene)
{
	scene->parent = this;
	this->children.push_back(scene);
}

IScene* IScene::findSceneById(int id)
{
	if (id == this->id) {
		return this;
	}
	for (auto c : children) {
		auto s = c->findSceneById(id);
		if (s != nullptr) {
			return s;
		}
	}
	return nullptr;
}

void IScene::deleteSceneById(int id)
{	
	for (auto c : children) {
		if (c->getId() == id) {
			children.remove(c);
			delete c;
			return;
		}
	}
}

IScene* IScene::findSceneByName(const std::string& name)
{
	if (name == this->name) {
		return this;
	}
	for (auto c : children) {
		if (c->findSceneByName(name) != nullptr) {
			return c;
		}
	}
	return nullptr;
}

IScene* IScene::getRoot()
{
	auto p = this;
	while (!p->isRoot()) {
		p = p->getParent();
	}
	return p;
}

std::list<IScene*> IScene::findScenes(const SceneType type)
{
	std::list<IScene*> scenes;
	if (this->getType() == type) {
		scenes.push_back(this);
	}
	//scenes.push_back(this);
	for (auto c : children) {
		auto ss = c->findScenes(type);
		scenes.splice(scenes.end(), ss);
	}
	return scenes;
}