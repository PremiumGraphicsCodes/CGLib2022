#pragma once

#include "Crystal/Shader/TextureObject.h"
#include "Crystal/Shader/OnScreenRenderer.h"

#include "ScreenShader.h"
#include "ScreenIdShader.h"

#include "IShaderScene.h"

#include "Crystal/Util/UnCopyable.h"
#include "RendererRepository.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {

enum RenderTarget
{
	Shaded,
	ParentId,
	ChildId,
	Custom,
};

class SceneShader
{
public:
	SceneShader();

	~SceneShader() {}

	Shader::ShaderBuildStatus build();

	void release();

	void render(const Graphics::Camera& camera);

	void render(const Graphics::Camera& camera, const int width, const int height);

	ScreenShader* getObjectRenderer() { return objectRenderer.get(); }

	ScreenIdShader* getParentIdRenderer() { return parentIdRenderer.get(); }

	ScreenIdShader* getChildIdRenderer() { return childIdRenderer.get(); }

	void setRenderTarget(const RenderTarget target) { this->target = target; }

	Shader::GLObjectFactory* getGLFactory() { return &glFactory; }

	RendererRepository* getRenderers() { return &renderers; }

private:
	std::unique_ptr<ScreenShader> objectRenderer;
	std::unique_ptr<ScreenIdShader> parentIdRenderer;
	std::unique_ptr<ScreenIdShader> childIdRenderer;
	std::unique_ptr<IScreenShader> customRenderer;

	RendererRepository renderers;

	RenderTarget target;

	Shader::GLObjectFactory glFactory;
};

	}
}