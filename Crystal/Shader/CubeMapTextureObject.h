#ifndef __CRYSTAL_SHADER_CUBE_MAP_TEXTURE_OBJECT_H__
#define __CRYSTAL_SHADER_CUBE_MAP_TEXTURE_OBJECT_H__

#include "../Graphics/Imagef.h"
#include "ITextureObject.h"

#include <array>

namespace Crystal {
	namespace Shader {

class CubeMapTextureObject : public ITextureObject
{
public:
	void create(const std::array<Graphics::Imagef, 6>& images);

	void setPositiveX(const Graphics::Imagef& image);

	void setNegativeX(const Graphics::Imagef& image);

	void setPositiveY(const Graphics::Imagef& image);

	void setNegativeY(const Graphics::Imagef& image);

	void setPositiveZ(const Graphics::Imagef& image);

	void setNegativeZ(const Graphics::Imagef& image);

	void bind(const int slotNumber) const override;

	void unbind() const override;

	void clear() override;

private:
};

	}
}

#endif