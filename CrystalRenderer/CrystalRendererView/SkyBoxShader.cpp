#include "SkyBoxShader.h"

#include "CrystalRenderer/CrystalRenderer/SkyBoxRenderer.h"

#include "Crystal/Shader/FrameBufferObject.h"
#include "Crystal/Shader/TextureObject.h"

#include "Crystal/IO/ImageFileReader.h"

using namespace Crystal::IO;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

namespace {
	bool readCubeMap(CubeMapTextureObject& cubeMap)
	{
		ImageFileReader reader;
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/posx.jpg")) {
			return false;
		}
		std::array<Image, 6> images;
		images[0] = reader.getImage();
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/negx.jpg")) {
			return false;
		}
		images[1] = reader.getImage();
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/posy.jpg")) {
			return false;
		}
		images[2] = reader.getImage();
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/negy.jpg")) {
			return false;
		}
		images[3] = reader.getImage();
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/posz.jpg")) {
			return false;
		}
		images[4] = reader.getImage();
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/negz.jpg")) {
			return false;
		}
		images[5] = reader.getImage();
		//		CubeMapTextureObject cubeMap;
		cubeMap.create(images);
		return true;
	}
}

ShaderBuildStatus SkyBoxShader::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;

	status.add(skyBoxRenderer.build(factory));

	this->cubeMapTexture = new CubeMapTextureObject();
	factory.add(cubeMapTexture);
	readCubeMap(*this->cubeMapTexture);

	return status;
}

void SkyBoxShader::release(GLObjectFactory& factory)
{

}

void SkyBoxShader::render(const Camera& camera, const int width, const int height)
{
	{

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SkyBoxRenderer::Buffer buffer;
		buffer.modelViewMatrix = glm::mat4(glm::mat3(camera.getModelViewMatrix()));
		buffer.projectionMatrix = camera.getProjectionMatrix();
		buffer.cubeMapTexture = this->cubeMapTexture;

		skyBoxRenderer.render(buffer);

	}
}
