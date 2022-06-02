#pragma once

#include "ShaderObject.h"

namespace Crystal {
	namespace Shader {
		class DepthTextureObject;

class DepthRenderer
{
public:
	void render(const DepthTextureObject& depthTexture);

	bool build();
private:
	ShaderObject shader;

	std::string getBuiltinVertexShaderSource();

	std::string getBuiltinFragmentShaderSource();

	void findLocation();
};

	}
}