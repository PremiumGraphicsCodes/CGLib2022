#pragma once

#include "glew.h"
#include "../Graphics/Image.h"
#include "IGLObject.h"

namespace Crystal {
	namespace Shader {
		class ITextureObject;

class FrameBufferObject : IGLObject
{
//private:
//	FrameBufferObject() {};

public:
	void build(int width, int height);

	void clear() override;

	void setTexture(const ITextureObject& texture);

	void bind();

	void unbind();

	Graphics::Image toImage() const;

	Graphics::ColorRGBAuc getColor(const int x, const int y) const;

	Graphics::ColorRGBAf getColorf(const int x, const int y) const;

	std::vector<Graphics::ColorRGBAuc> getColors(const int x, const int y, const int width, const int height) const;

	std::vector<Graphics::ColorRGBAf> getColorsf(const int x, const int y, const int width, const int height) const;

	int getWidth() const { return width; }

	int getHeight() const { return height; }

private:
	GLuint frameBuffer;
	GLuint depthBuffer;
	int width;
	int height;
};

	}
}