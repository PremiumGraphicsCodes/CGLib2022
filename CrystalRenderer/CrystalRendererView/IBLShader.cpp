#include "IBLShader.h"
#include "../../Crystal/Shader/ShaderObject.h"

#include "../../Crystal/ThirdParty/stb/stb_image.h"

#include <iostream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

namespace 
{
	void loadTexture()
	{
		stbi_set_flip_vertically_on_load(true);
		int width, height, nrComponents;
		float* data = stbi_loadf("../../ThirdParty/hdr/newport_loft.hdr", &width, &height, &nrComponents, 0);
		unsigned int hdrTexture;
		if (data)
		{
			glGenTextures(1, &hdrTexture);
			glBindTexture(GL_TEXTURE_2D, hdrTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load HDR image." << std::endl;
		}
	}
}

ShaderBuildStatus IBLShader::build()
{
	loadTexture();

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
	return status;
}

void IBLShader::render(const Camera& camera, const int width, const int height)
{

}

