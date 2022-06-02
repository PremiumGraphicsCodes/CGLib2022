#pragma once

#include "IScene.h"
#include "Crystal/Graphics/Camera.h"

namespace Crystal {
	namespace Scene {

class CameraScene : public IScene
{
public:
	CameraScene(const int id, const std::string& name, Graphics::Camera* camera);

	~CameraScene() {};

	Graphics::Camera* getCamera() const { return camera.get(); }

	IPresenter* getPresenter() { return nullptr; }

	SceneType getType() const { return SceneTypeLabels::CameraScene; }

private:
	std::unique_ptr< Graphics::Camera > camera;

};

	}
}