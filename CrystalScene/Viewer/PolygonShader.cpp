#include "PolygonShader.h"

#include "CrystalScene/Scene/PolygonRenderer.h"

#include "Crystal/Shader/FrameBufferObject.h"
#include "Crystal/Shader/TextureObject.h"

#include "Crystal/IO/ImageFileReader.h"

using namespace Crystal::IO;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

ShaderBuildStatus PolygonShader::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;

	status.add(renderer.build(factory));

	this->fbo = factory.createFrameBufferObject();
	this->fbo->build(512, 512);

	this->texture = factory.createTextureObject();
	this->texture->send(Image(512, 512));

	/*
	this->cubeMapTexture = new CubeMapTextureObject();
	factory.add(cubeMapTexture);
	readCubeMap(*this->cubeMapTexture);
	*/

	return status;
}

void PolygonShader::release(GLObjectFactory& factory)
{
	factory.remove(this->fbo);
	factory.remove(this->texture);
}

void PolygonShader::render(const Camera& camera)
{
	{
		this->fbo->bind();
		this->fbo->setTexture(*this->texture);

		glViewport(0, 0, texture->getWidth(), texture->getHeight());
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//SkyBoxRenderer::Buffer buffer;
		//buffer.modelViewMatrix = glm::mat4(glm::mat3(camera.getModelViewMatrix()));
		//buffer.projectionMatrix = camera.getProjectionMatrix();
		//buffer.cubeMapTexture = this->cubeMapTexture;

		//skyBoxRenderer.render(buffer);

		this->fbo->unbind();
	}
}

TextureObject* PolygonShader::getTexture()
{
	return this->texture;
}

