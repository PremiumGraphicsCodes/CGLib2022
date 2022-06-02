#pragma once

#include "glew.h"
#include "../Graphics/Imagef.h"
#include "ITextureObject.h"

namespace Crystal {
	namespace Shader {

class DepthTextureObject : public ITextureObject
{
public:
	DepthTextureObject();

	void send(const Graphics::Imagef& image);

	void bind(const int slotNumber) const override;

	void unbind() const override;

	void clear() override;
};

	}
}