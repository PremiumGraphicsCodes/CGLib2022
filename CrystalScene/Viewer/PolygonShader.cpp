#include "PolygonShader.h"

#include "CrystalScene/Scene/PolygonRenderer.h"

#include "Crystal/Shader/FrameBufferObject.h"
#include "Crystal/Shader/TextureObject.h"

#include "Crystal/IO/ImageFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

namespace {
	bool readTexture(TextureObject& cubeMap)
	{
		ImageFileReader reader;
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/posx.jpg")) {
			return false;
		}
		cubeMap.send(reader.getImage());
		return true;
	}
}


ShaderBuildStatus PolygonShader::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;

	status.add(renderer.build(factory));
	status.add(gRenderer.build(factory));

	this->fbo = factory.createFrameBufferObject();
	this->fbo->build(512, 512);

	this->texture = factory.createTextureObject();
	this->texture->send(Image(512, 512));

	this->polygonTexture = factory.createTextureObject();
	this->polygonTexture->send(Image(512, 512, 255));

	this->geometryTexture = factory.createTextureObject();
	this->geometryTexture->send(Imagef(512, 512));

	readTexture(*this->polygonTexture);

	positions.add(Vector3dd(0.0, 0.0, 0.0));
	positions.add(Vector3dd(1.0, 0.0, 0.0));
	positions.add(Vector3dd(1.0, 1.0, 0.0));
	positions.add(Vector3dd(0.0, 1.0, 0.0));

	texCoords.add(Vector2dd(0.0, 0.0));
	texCoords.add(Vector2dd(1.0, 0.0));
	texCoords.add(Vector2dd(1.0, 1.0));
	texCoords.add(Vector2dd(0.0, 1.0));

	buffer.position.build();
	buffer.texCoord.build();

	gBuffer.position.build();

	Shader::PolygonRenderer::Buffer::FaceGroup fg1;
	fg1.indices.push_back(0);
	fg1.indices.push_back(1);
	fg1.indices.push_back(2);

	fg1.indices.push_back(0);
	fg1.indices.push_back(2);
	fg1.indices.push_back(3);

	fg1.texture = this->polygonTexture;
	buffer.faceGroups.push_back(fg1);

	gBuffer.indices = fg1.indices;

	//Shader::PolygonRenderer::Buffer::FaceGroup fg2;
	//fg2.indices.push_back(0);
	//fg2.indices.push_back(2);
	//fg2.indices.push_back(3);

	//fg2.texture = this->polygonTexture;
	//buffer.faceGroups.push_back(fg2);


	return status;
}

void PolygonShader::release(GLObjectFactory& factory)
{
	factory.remove(this->fbo);
	factory.remove(this->texture);
}

void PolygonShader::render(const Camera& camera)
{
	/*
	{
		this->fbo->bind();
		this->fbo->setTexture(*this->texture);

		glViewport(0, 0, texture->getWidth(), texture->getHeight());
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		buffer.position.send(positions.get());
		buffer.texCoord.send(texCoords.get());
		buffer.projectionMatrix = camera.getProjectionMatrix();
		buffer.modelViewMatrix = camera.getModelViewMatrix();

		this->renderer.render(buffer);

		this->fbo->unbind();
	}
	*/

	{
		this->fbo->bind();
		this->fbo->setTexture(*geometryTexture);

		glViewport(0, 0, texture->getWidth(), texture->getHeight());
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gBuffer.position.send(positions.get());
		gBuffer.projectionMatrix = camera.getProjectionMatrix();
		gBuffer.modelViewMatrix = camera.getModelViewMatrix();

		this->gRenderer.render(gBuffer);

		this->fbo->unbind();
	}
}

TextureObject* PolygonShader::getTexture()
{
	return this->geometryTexture;//this->texture;
}

