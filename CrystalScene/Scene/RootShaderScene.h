#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRootShaderScene.h"

#include "SceneRootShaderScene.h"
#include "SceneIdRootShaderScene.h"

#include "../Scene/ViewModel.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {

class RootShaderScene : private UnCopyable
{
public:
	RootShaderScene();

	~RootShaderScene() {}

	bool build(Shader::GLObjectFactory& factory);

	void render(const int width, const int height, const ViewModel& vm);

	SceneRenderer* getObjectRenderer() { return &objectRenderer; }

	SceneIdRenderer* getParentIdRenderer() { return &parentIdRenderer; }

	SceneIdRenderer* getChildIdRenderer() { return &childIdRenderer; }

	void setShowOffScreen(const bool b) { this->showOffScreen = b; }

	Graphics::Camera* getCamera() { return camera.get(); }

private:
	Shader::OnScreenRenderer renderer;

	SceneRenderer objectRenderer;
	SceneIdRenderer parentIdRenderer;
	SceneIdRenderer childIdRenderer;

	bool showOffScreen;

	std::unique_ptr<Graphics::Camera> camera;
};

	}
}