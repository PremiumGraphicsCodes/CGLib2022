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
	status.add(lightRenderer.build(factory));

	this->fbo = factory.createFrameBufferObject();
	this->fbo->build(512, 512);

	this->colorTexture = factory.createTextureObject();
	this->colorTexture->send(Image(512, 512));

	this->polygonTexture = factory.createTextureObject();
	this->polygonTexture->send(Image(512, 512, 255));

	this->geometryTexture = factory.createTextureObject();
	this->geometryTexture->send(Imagef(512, 512));

	this->normalTexture = factory.createTextureObject();
	this->normalTexture->send(Imagef(512, 512));

	readTexture(*this->polygonTexture);

	positions.add(Vector3dd(0.0, 0.0, 0.0));
	positions.add(Vector3dd(1.0, 0.0, 0.0));
	positions.add(Vector3dd(1.0, 1.0, 0.0));
	positions.add(Vector3dd(0.0, 1.0, 0.0));

	texCoords.add(Vector2dd(0.0, 0.0));
	texCoords.add(Vector2dd(1.0, 0.0));
	texCoords.add(Vector2dd(1.0, 1.0));
	texCoords.add(Vector2dd(0.0, 1.0));

	normals.add(Vector3dd(0, 0, 1));
	normals.add(Vector3dd(0, 0, 1));
	normals.add(Vector3dd(0, 0, 1));
	normals.add(Vector3dd(0, 0, 1));

	buffer.position.build();
	buffer.texCoord.build();

	gBuffer.position.build();
	gBuffer.normal.build();

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
	factory.remove(this->colorTexture);
}

void PolygonShader::render(const Camera& camera)
{
	const int width = 512;
	const int height = 512;
	{
		this->fbo->bind();
		this->fbo->setTexture(*this->colorTexture);

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		buffer.position.send(positions.get());
		buffer.texCoord.send(texCoords.get());
		buffer.projectionMatrix = camera.getProjectionMatrix();
		buffer.modelViewMatrix = camera.getModelViewMatrix();

		this->renderer.render(buffer);

		this->fbo->unbind();
	}

	{
		this->fbo->bind();

		const GLenum bufs[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, bufs);

		//this->geometryTexture->bind(0);
		this->fbo->setTexture(*geometryTexture);
		//this->normalTexture->bind(1);
		this->fbo->setTexture(*normalTexture, 1);

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gBuffer.position.send(positions.get());
		gBuffer.normal.send(normals.get());
		gBuffer.projectionMatrix = camera.getProjectionMatrix();
		gBuffer.modelViewMatrix = camera.getModelViewMatrix();
		gBuffer.normalMatrix = glm::transpose(glm::inverse(glm::mat3(camera.getRotationMatrix())));

		this->gRenderer.render(gBuffer);

		this->fbo->unbind();

		//const GLenum bufs1[] = { GL_COLOR_ATTACHMENT0 };
		//glDrawBuffers(1, bufs1);
	}
}

TextureObject* PolygonShader::getTexture()
{
	return this->normalTexture;//this->geometryTexture;//this->texture;
}