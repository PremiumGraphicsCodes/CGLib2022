#pragma once

#include <list>
#include <string>
#include "SceneType.h"

#include "Crystal/Math/Box3d.h"
#include "Crystal/Graphics/Camera.h"
#include "Crystal/Shader/GLObjectFactory.h"

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {

class IScene
{
public:
	IScene();

	explicit IScene(const int id);

	IScene(const int id, const std::string& name);

	virtual ~IScene();

	void clear();

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	void setId(const int id) { this->id = id; }

	int getId() const { return id; }

	bool isVisible() const { return _isVisible; }

	void setVisible(const bool b) { this->_isVisible = b; }

	//void setVisible(const bool b) { this->_isVisible = b; }

	bool _isVisible;

	bool _isPickable;

	bool isPickable() const { return _isPickable; }

	virtual SceneType getType() const = 0;

	void addScene(IScene* scene);

	IScene* findSceneById(int id);

	IScene* findSceneByName(const std::string& name);

	void deleteSceneById(int id);

	template<class T>
	T findSceneById(int id) { return static_cast<T>( findSceneById(id) ); }

	template<class T>
	T findSceneByName(const std::string& name) { return static_cast<T>(findSceneByName(name)); }

	std::list<IScene*> findScenes(SceneType type);

	virtual Math::Box3dd getBoundingBox() const { return Math::Box3dd::createDegeneratedBox(); }

	bool isRoot() const { return parent == nullptr; }

	IScene* getParent() const { return parent; }

	IScene* getRoot();

	std::list<IScene*> getChildren() const { return children; }

	bool isLeaf() const { return children.empty(); }

	virtual IPresenter* getPresenter() = 0;

protected:
	std::string name;
	int id;
	std::list<IScene*> children;
	IScene* parent;
};
	}
}