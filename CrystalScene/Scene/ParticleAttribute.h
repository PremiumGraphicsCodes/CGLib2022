#pragma once

#include "Crystal/Graphics/ColorRGBA.h"
#include "Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Scene {

struct ParticleAttribute : Shape::IParticleAttribute
{
	Graphics::ColorRGBAf color;
};

	}
}