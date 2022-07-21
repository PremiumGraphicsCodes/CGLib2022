#include "PolygonShaderView.h"

#include "PolygonShader.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PolygonShaderView::PolygonShaderView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas)
{}

void PolygonShaderView::onOk()
{
	auto factory = getWorld()->getRenderer()->getGLFactory();
	std::unique_ptr<PolygonShader> shader = std::make_unique<PolygonShader>();
	shader->build(*factory);
	getWorld()->getRenderer()->setCustomRenderer(std::move(shader));

	getWorld()->getRenderer()->setRenderTarget(RenderTarget::Custom);
}