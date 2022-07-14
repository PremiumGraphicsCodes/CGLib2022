#include "CubeMapShader.h"

#include "Crystal/Shader/SkyBoxRenderer.h"

using namespace Crystal::Shader;
using namespace Crystal::UI;

ShaderBuildStatus CubeMapShader::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;

	status.add( skyBoxRenderer.build(factory) );

	return status;
}

void CubeMapShader::release(GLObjectFactory& factory)
{

}

void CubeMapShader::render(const Graphics::Camera& camera)
{

}

TextureObject* CubeMapShader::getTexture()
{
	return nullptr;
}

