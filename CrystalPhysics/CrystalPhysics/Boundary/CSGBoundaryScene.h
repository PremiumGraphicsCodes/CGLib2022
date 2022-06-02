#pragma once

#include "CrystalScene/Scene/IScene.h"

namespace Crystal {
	namespace Physics {
		class CSGBoundaryScenePresenter;

class CSGBoundaryScene : public Scene::IScene
{
public:
	CSGBoundaryScene(const int id, const std::string& name);

	~CSGBoundaryScene();

	void clearBoxes() { boxes.clear(); }

	static constexpr auto Type = "CSGBoundaryScene";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter();

	void add(const Math::Box3dd& box) { boxes.push_back(box); }

	Math::Box3dd getBoundingBox() const override;

	std::list<Math::Box3dd> getBoxes() const { return boxes; }

private:
	std::list<Math::Box3dd> boxes;
	std::unique_ptr<CSGBoundaryScenePresenter> controller;
};

	}
}
