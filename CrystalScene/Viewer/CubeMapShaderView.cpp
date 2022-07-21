#include "CubeMapShaderView.h"

#include "CubeMapShader.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

CubeMapShaderView::CubeMapShaderView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas)
{}

void CubeMapShaderView::onOk()
{
	auto factory = getWorld()->getRenderer()->getGLFactory();
	std::unique_ptr<CubeMapShader> shader = std::make_unique<CubeMapShader>();
	shader->build(*factory);
	getWorld()->getRenderer()->setCustomRenderer(std::move(shader));

	getWorld()->getRenderer()->setRenderTarget(RenderTarget::Custom);
}