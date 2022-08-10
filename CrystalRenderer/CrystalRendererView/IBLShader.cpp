#include "IBLShader.h"
#include "../../Crystal/Shader/ShaderObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

ShaderBuildStatus IBLShader::build()
{
	ShaderBuildStatus status;
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

