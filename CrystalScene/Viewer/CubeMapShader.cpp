#include "CubeMapShader.h"

#include "Crystal/Shader/SkyBoxRenderer.h"

#include "Crystal/Shader/FrameBufferObject.h"
#include "Crystal/Shader/TextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

ShaderBuildStatus CubeMapShader::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;

	status.add( skyBoxRenderer.build(factory) );

	this->frameBufferObject = factory.createFrameBufferObject();
	this->frameBufferObject->build(512, 512);

	this->texture = factory.createTextureObject();
	this->texture->send(Image(512, 512));

	return status;
}

void CubeMapShader::release(GLObjectFactory& factory)
{
	factory.remove(this->frameBufferObject);
	factory.remove(this->texture);
}

void CubeMapShader::render(const Camera& camera)
{

}

TextureObject* CubeMapShader::getTexture()
{
	return this->texture;
}

