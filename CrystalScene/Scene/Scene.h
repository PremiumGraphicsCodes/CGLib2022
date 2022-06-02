#pragma once

#include "Crystal/Util/UnCopyable.h"
#include "IScene.h"

namespace Crystal {
	namespace Scene {

class Scene : public IScene
{
public:
	Scene(const int id, const std::string& name);

	~Scene();

	Math::Box3dd getBoundingBox() const;

	virtual SceneType getType() const { return SceneTypeLabels::Root; }

	IPresenter* getPresenter() override { return nullptr; }
private:
};
	}
}