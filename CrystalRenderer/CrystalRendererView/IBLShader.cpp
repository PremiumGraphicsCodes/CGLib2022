#include "IBLShader.h"
#include "../../Crystal/Shader/ShaderObject.h"
#include "../CrystalRenderer/HDRImage.h"

#include "../../Crystal/ThirdParty/glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

#include <filesystem>
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;
using namespace Crystal::UI;

namespace 
{

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


	class ShaderBuilder
	{
	public:
		std::unique_ptr<ShaderObject> build(const std::string& vsFile, const std::string& fsFile)
		{
			std::unique_ptr<ShaderObject> shader = std::make_unique<ShaderObject>();
			const auto isOk = shader->buildFromFile(vsFile, fsFile);
			if (!isOk) {
				status.log += shader->getLog();
			}
			return std::move(shader);
		}

	private:
		ShaderBuildStatus status;
	};


	/*
	class RendererFactory
	{
		void create(std::unique_ptr<ShaderObject> shader, IRenderer& renderer)
		{
			renderer.setShader(std::move(shader));
			renderer.link();
		}
	};
	*/

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

	ShaderBuilder shaderBuilder;

	ShaderBuildStatus status;
	{
		auto shader = shaderBuilder.build("../GLSL/CubeMap.vs", "../GLSL/CubeMap.fs");
		renderers.cubeMapRenderer.setShader(std::move(shader));
		renderers.cubeMapRenderer.link();
	}

	{
		auto shader = shaderBuilder.build("../GLSL/Irradiance.vs", "../GLSL/Irradiance.fs");
		renderers.irradianceRenderer.setShader(std::move(shader));
		renderers.irradianceRenderer.link();
	}

	{
		auto shader = shaderBuilder.build("../GLSL/IBLDiffuse.vs", "../GLSL/IBLDiffuse.fs");
		renderers.diffuseRenderer.setShader(std::move(shader));
		renderers.diffuseRenderer.link();
	}

	{
		auto shader = shaderBuilder.build("../GLSL/BRDFLUT.vs", "../GLSL/BRDFLUT.fs");
		renderers.brdfLutRenderer.setShader(std::move(shader));
		renderers.brdfLutRenderer.link();
	}

	{
		auto shader = shaderBuilder.build("../GLSL/Importance.vs", "../GLSL/Importance.fs");
		renderers.importanceRenderer.setShader(std::move(shader));
		renderers.importanceRenderer.link();
	}

	{
		auto shader = shaderBuilder.build("../GLSL/IBLSpecular.vs", "../GLSL/IBLSpecular.fs");
	}

	{
		auto shader = shaderBuilder.build("../GLSL/SkyBox.vs", "../GLSL/SkyBox.fs");
		renderers.skyBoxRenderer.setShader(std::move(shader));
		renderers.skyBoxRenderer.link();
	}

	{
		positions.add(Vector3dd(0.0, 0.0, 0.0));
		positions.add(Vector3dd(1.0, 0.0, 0.0));
		positions.add(Vector3dd(1.0, 1.0, 0.0));
		positions.add(Vector3dd(0.0, 1.0, 0.0));

		normals.add(Vector3dd(0, 0, 1));
		normals.add(Vector3dd(0, 0, 1));
		normals.add(Vector3dd(0, 0, 1));
		normals.add(Vector3dd(0, 0, 1));

		positionVBO.build();
		positionVBO.send(positions.get());

		normalVBO.build();
		normalVBO.send(normals.get());

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
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

			renderers.cubeMapRenderer.buffer.projectionMatrix = ::captureProjection;
			renderers.cubeMapRenderer.buffer.viewMatrix = ::captureViews[i];
			renderers.cubeMapRenderer.buffer.texture = &this->hdrTex;

			renderers.cubeMapRenderer.render();
		}

		this->cubeMapTex.unbind();
		this->fbo.unbind();
	}

	{
		this->fbo.bind();

		renderers.irradianceRenderer.buffer.cubeMapTex = &cubeMapTex;

		for (int i = 0; i < 6; ++i) {
			glViewport(0, 0, 32, 32);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->irradianceTex.getHandle(), 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderers.irradianceRenderer.buffer.projectionMatrix = ::captureProjection;
			renderers.irradianceRenderer.buffer.viewMatrix = ::captureViews[i];
			renderers.irradianceRenderer.buffer.cubeMapTex = &this->cubeMapTex;

			renderers.irradianceRenderer.render();
		}

		this->fbo.unbind();

	}

	/*
	{

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderers.skyBoxRenderer.buffer.modelViewMatrix = glm::mat4(glm::mat3(camera.getModelViewMatrix()));
		renderers.skyBoxRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		renderers.skyBoxRenderer.buffer.cubeMapTexture = &this->cubeMapTex;

		renderers.skyBoxRenderer.render();

	}
	*/

	/*
	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		diffuseRenderer.buffer.modelMatrix = camera.getModelMatrix();
		diffuseRenderer.buffer.viewMatrix = camera.getViewMatrix();
		diffuseRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		diffuseRenderer.buffer.eyePosition = camera.getEye();
		diffuseRenderer.buffer.irradianceMapTex = &this->irradianceTex;
		diffuseRenderer.buffer.position = &this->positionVBO;
		diffuseRenderer.buffer.normal = &this->normalVBO;
		diffuseRenderer.buffer.albedo = Vector3df(1, 0, 0);
		diffuseRenderer.buffer.metalic = 0.7;
		diffuseRenderer.buffer.ao = 0.5;
		diffuseRenderer.buffer.indices = indices;

		diffuseRenderer.render();
	}
	*/

	/*
	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		brdfLutRenderer.render();
	}
	*/

	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderers.importanceRenderer.buffer.evnMapTex = &cubeMapTex;
		renderers.importanceRenderer.buffer.positions = &positionVBO;
		renderers.importanceRenderer.buffer.indices = this->indices;
		renderers.importanceRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		renderers.importanceRenderer.buffer.viewMatrix = camera.getViewMatrix();
		renderers.importanceRenderer.buffer.roughness = 0.1f;
		
		renderers.importanceRenderer.render();
	}
}