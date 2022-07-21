#pragma once

#include "Crystal/Shader/ShaderBuildStatus.h"
#include "Crystal/Shader/PointRenderer.h"
#include "Crystal/Shader/LineRenderer.h"
#include "Crystal/Shader/TriangleRenderer.h"
#include "Crystal/Shader/OnScreenRenderer.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class ScreenShaderScene;

class RendererRepository
{
public:
	RendererRepository();

	~RendererRepository();

	Shader::ShaderBuildStatus build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	Shader::PointRenderer* getPointShader() { return pointRenderer.get(); }

	Shader::LineRenderer* getWireShader() { return wireRenderer.get(); }

	Shader::TriangleRenderer* getTriangleShader() { return triagleRenderer.get(); }

	Shader::OnScreenRenderer* getOnScreenShader() { return onScreenRenderer.get(); }

	void addRenderer(std::unique_ptr<Shader::IRenderer> renderer);

	Shader::IRenderer* findRenderer(const std::string& name);

private:
	std::unique_ptr<Shader::PointRenderer> pointRenderer;
	std::unique_ptr<Shader::LineRenderer> wireRenderer;
	std::unique_ptr<Shader::TriangleRenderer> triagleRenderer;
	std::unique_ptr<Shader::OnScreenRenderer> onScreenRenderer;
	std::vector<std::unique_ptr<Shader::IRenderer>> customRenderers;
};

	}
}