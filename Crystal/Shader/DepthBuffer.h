#pragma once

#include "DepthTextureObject.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace Shader {

class DepthBuffer
{
public:
	~DepthBuffer() {
		unbind();
	}

	void setTexture(DepthTextureObject* texture);

	bool build(DepthTextureObject* depthTexture);

	bool bind(const int slotNumber) const;

	bool unbind() const;

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	DepthTextureObject* getTexture() { return texture; }

private:
	GLuint frameBuffer;
	DepthTextureObject* texture;
	int width;
	int height;
};

	}
}