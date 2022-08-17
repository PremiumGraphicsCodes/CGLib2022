#include "BRDFLUTRenderer.h"

#include "Crystal/Math/Box2d.h"

using namespace Crystal::Math;
using namespace Crystal::Renderer;

namespace {
	constexpr auto positionLabel = "aPos";
	constexpr auto texCoordLabel = "aTexCoords";
	constexpr auto fragColorLabel = "FragColor";
}

BRDFLUTRenderer::BRDFLUTRenderer()
{
}

void BRDFLUTRenderer::link()
{
	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::texCoordLabel);
}

namespace {
	std::vector<float> toArray(const Box2d<float>& box)
	{
		return{
			box.getMinX(), box.getMaxY(),
			box.getMinX(), box.getMinY(),
			box.getMaxX(), box.getMinY(),
			box.getMaxX(), box.getMaxY()
		};
	}

	std::vector<float> getTexCoords()
	{
		return {
			0.0, 1.0,
			0.0, 0.0,
			1.0, 0.0,
			1.0, 1.0
		};
	}
}

void BRDFLUTRenderer::render()
{
	const Box2d<float> box(Vector2df(-1.0, -1.0), Vector2df(1.0, 1.0));
	const auto positions = ::toArray(box);
	const auto texCoords = getTexCoords();

	shader->bind();
	shader->bindOutput(::fragColorLabel, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	shader->sendVertexAttribute2df(::positionLabel, positions);
	shader->sendVertexAttribute2df(::texCoordLabel, texCoords);
	shader->drawQuads(positions.size() / 2);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	shader->unbind();
}