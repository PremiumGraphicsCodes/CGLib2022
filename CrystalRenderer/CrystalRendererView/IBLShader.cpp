#include "IBLShader.h"
#include "../../Crystal/Shader/ShaderObject.h"

#include "../../Crystal/ThirdParty/stb/stb_image.h"

#include "../../Crystal/ThirdParty/glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

#include <filesystem>
#include <iostream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

namespace 
{
	class HDRImage
	{
	public:
		bool load(const std::filesystem::path& path)
		{
			stbi_set_flip_vertically_on_load(true);
			int nrComponents;
			float* d = stbi_loadf(path.string().c_str(), &width, &height, &nrComponents, 0);
			if (d == nullptr) {
				return false;
			}
			const auto size = width * height * nrComponents;
			this->data.resize(size);
			for (int i = 0; i < size; ++i) {
				this->data[i] = d[i];
			}
			stbi_image_free(d);
			return true;
		}

		std::vector<float> data;
		int width;
		int height;
	};

	void sendHDRTexture(const HDRImage& hdr, TextureObject& hdrTex)
	{
		hdrTex.bind(0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, hdr.width, hdr.height, 0, GL_RGB, GL_FLOAT, hdr.data.data());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		hdrTex.unbind();
	}

	glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	glm::mat4 captureViews[] =
	{
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};

}

ShaderBuildStatus IBLShader::build()
{
	HDRImage hdr;
	hdr.load(std::filesystem::path("../../ThirdParty/hdr/newport_loft.hdr"));
	hdrTex.create("");
	sendHDRTexture(hdr, hdrTex);

	fbo.build(512, 512);

	std::array<Graphics::Image, 6> images;
	for (int i = 0; i < 6; ++i) {
		Graphics::Image im(512, 512, 0);
		images[i] = im;
	}
	cubeMapTex.create(images);

	irradianceTex.create();
	glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceTex.getHandle());
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	irradianceTex.unbind();

	ShaderBuildStatus status;
	{
		std::unique_ptr<ShaderObject> shader = std::make_unique<ShaderObject>();
		const auto isOk = shader->buildFromFile("../GLSL/CubeMap.vs", "../GLSL/CubeMap.fs");
		if (!isOk) {
			status.log += shader->getLog();
		}
		cubeMapRenderer.setShader(std::move(shader));
		cubeMapRenderer.link();
	}
	{
		std::unique_ptr<ShaderObject> shader = std::make_unique<ShaderObject>();
		const auto isOk = shader->buildFromFile("../GLSL/Irradiance.vs", "../GLSL/Irradiance.fs");
		if (!isOk) {
			status.log += shader->getLog();
		}
		irradianceRenderer.setShader(std::move(shader));
		irradianceRenderer.link();
	}

	{
		std::unique_ptr<ShaderObject> shader = std::make_unique<ShaderObject>();
		const auto isOk = shader->buildFromFile("../GLSL/SkyBox.vs", "../GLSL/SkyBox.fs");
		if (!isOk) {
			status.log += shader->getLog();
		}
		skyBoxRenderer.setShader(std::move(shader));
		skyBoxRenderer.link();
	}
	return status;
}

void IBLShader::render(const Camera& camera, const int width, const int height)
{
	{
		this->fbo.bind();
		//this->cubeMapTex.bind(0);

		for (int i = 0; i < 6; ++i) {
			glViewport(0, 0, 512, 512);
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->cubeMapTex.getHandle(), 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			cubeMapRenderer.buffer.projectionMatrix = ::captureProjection;
			cubeMapRenderer.buffer.viewMatrix = ::captureViews[i];
			cubeMapRenderer.buffer.texture = &this->hdrTex;

			cubeMapRenderer.render();
		}

		this->cubeMapTex.unbind();
		this->fbo.unbind();
	}

	{
		this->fbo.bind();

		irradianceRenderer.buffer.cubeMapTex = &cubeMapTex;

		for (int i = 0; i < 6; ++i) {
			glViewport(0, 0, 32, 32);
			//glClea
		}

		this->fbo.unbind();

	}

	{

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skyBoxRenderer.buffer.modelViewMatrix = glm::mat4(glm::mat3(camera.getModelViewMatrix()));
		skyBoxRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		skyBoxRenderer.buffer.cubeMapTexture = &this->cubeMapTex;

		skyBoxRenderer.render();

	}
}

