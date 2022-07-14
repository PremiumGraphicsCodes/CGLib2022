#include "CubeMapView.h"

#include "Crystal/Shader/SkyBoxRenderer.h"
#include "CubeMapShader.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

CubeMapView::CubeMapView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas)
{}

void CubeMapView::onOk()
{
	auto factory = getWorld()->getRenderer()->getGLFactory();
	CubeMapShader shader;
	shader.build(*factory);
	//getWorld()->getRenderer()->setCustomRenderer();
}