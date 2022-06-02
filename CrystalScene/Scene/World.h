#pragma once

#include "Crystal/Util/UnCopyable.h"

#include "Scene.h"
#include "SceneIdProvider.h"

#include "SceneShader.h"

#include "CameraScene.h"

#include "Crystal/Shader/GLObjectFactory.h"
#include "IAnimator.h"

#include <filesystem>

namespace Crystal {
	namespace Scene {
		class IAnimator;

class World : private UnCopyable
{
public:
	World();

	~World();

	void init();

	void clear();

	Scene* getScenes() { return scene.get(); }

	void addScene(IScene* scene);

	int getNextSceneId() { return sceneIdProvider.getNextId(); }

	Math::Box3dd getBoundingBox() const;

	SceneShader* getRenderer() { return renderer.get(); }

	CameraScene* getCamera() { return camera; }

	std::list<IAnimator*> getAnimations() const { return animations; }

	void addAnimation(IAnimator* a) { this->animations.push_back(a); }

	template<typename T>
	T findAnimatorById(const int id) const {
		auto iter = std::find_if(animations.begin(), animations.end(), [id](IAnimator* a) { return id == a->getId(); });
		return static_cast<T>(*iter);
	}

	int createDefaultCamera();

	void addPresenter(IPresenter* p) { this->presenters.push_back(p); }

	template<typename T>
	T findPresenterById(const int id) const {
		auto iter = std::find_if(presenters.begin(), presenters.end(), [id](IPresenter* a) { return id == a->getId(); });
		return static_cast<T>(*iter);
	}

private:
	std::unique_ptr<Scene> scene;
	std::list<IAnimator*> animations;
	std::list<IPresenter*> presenters;
	CameraScene* camera;

	SceneIdProvider sceneIdProvider;
	
	std::unique_ptr<SceneShader> renderer;

};
	}
}