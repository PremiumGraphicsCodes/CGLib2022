#ifndef __CRYSTAL_GRAPHICS_COLOR_RGBA_H__
#define __CRYSTAL_GRAPHICS_COLOR_RGBA_H__

#include <vector>
#include <array>

#include "../Math/glm.h"

namespace Crystal {
	namespace Graphics {

using ColorRGBAf = glm::vec4;
using ColorRGBAuc = glm::u8vec4;

static ColorRGBAuc toColorRGBAuc(const ColorRGBAf& color)
{
	const auto r = static_cast<unsigned char>( color.r * 255 );
	const auto g = static_cast<unsigned char>( color.g * 255 );
	const auto b = static_cast<unsigned char>( color.b * 255 );
	const auto a = static_cast<unsigned char>( color.a * 255 );
	return ColorRGBAuc(r, g, b, a);
}

	}
}

#endif