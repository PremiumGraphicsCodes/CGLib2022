#include "SceneShader.h"

#include "Crystal/Graphics/Camera.h"

#include "Crystal/Shader/GLObjectFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneShader::SceneShader() :
	objectRenderer(std::make_unique<ScreenShader>("ObjectRenderer")),
	parentIdRenderer(std::make_unique<ScreenIdShader>("ParentIdRenderer")),
	childIdRenderer(std::make_unique<ScreenIdShader>("ChildIdRenderer")),
	target(RenderTarget::Shaded)
{
}

ShaderBuildStatus SceneShader::build()
{
	ShaderBuildStatus status = renderers.build(this->glFactory);

	const auto prStatus = objectRenderer->build(this->glFactory);
	parentIdRenderer->build(this->glFactory);
	childIdRenderer->build(this->glFactory);

	status.add(prStatus);
	//status.add(pIdStatus);
	//status.add(cIdStatus);

	return status;
}

void SceneShader::release()
{
	renderers.release(this->glFactory);

	objectRenderer->release(this->glFactory);
	parentIdRenderer->release(this->glFactory);
	childIdRenderer->release(this->glFactory);
}

void SceneShader::render(const Camera& camera)
{
	objectRenderer->render(camera);
	parentIdRenderer->render(camera);
	childIdRenderer->render(camera);

	/*
	if (customRenderer != nullptr) {
		customRenderer->render(camera);
	}
	*/
}

void SceneShader::render(const Graphics::Camera& camera, const int width, const int height)
{
	render(camera);
	glViewport(0, 0, width, height);
	//glClearColor(0.0, 0.0, 1.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const auto renderer = renderers.getOnScreenShader();

	switch (target) {
	case RenderTarget::Shaded:
	{
		auto texture = objectRenderer->getTexture();
		renderer->render(*texture);
		break;
	}
	case RenderTarget::ParentId:
	{
		auto texture = parentIdRenderer->getTextureScene();
		renderer->render(*texture);
		break;
	}
	case RenderTarget::ChildId:
	{
		auto texture = childIdRenderer->getTextureScene();
		renderer->render(*texture);
		break;
	}
	case RenderTarget::Custom:
	{
		auto texture = customRenderer->getTexture();
		renderer->render(*texture);
	}
	default:
		assert(false);
	}
}