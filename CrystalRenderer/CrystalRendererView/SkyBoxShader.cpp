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

ShaderBuildStatus SkyBoxShader::build()
{
	ShaderBuildStatus status;

	{
		std::unique_ptr<ShaderObject> shader = std::make_unique<ShaderObject>();
		const auto isOk = shader->buildFromFile("../GLSL/SkyBox.vs", "../GLSL/SkyBox.fs");
		if (!isOk) {
			status.log += shader->getLog();
		}
		skyBoxRenderer.setShader(std::move(shader));
	}

	//status.add(skyBoxRenderer.build(factory));

	this->cubeMapTexture = std::make_unique<CubeMapTextureObject>();
	readCubeMap(*this->cubeMapTexture);

	return status;
}

void SkyBoxShader::render(const Camera& camera, const int width, const int height)
{
	{

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skyBoxRenderer.buffer.modelViewMatrix = glm::mat4(glm::mat3(camera.getModelViewMatrix()));
		skyBoxRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		skyBoxRenderer.buffer.cubeMapTexture = this->cubeMapTexture.get();

		skyBoxRenderer.render();

	}
}
