#pragma once

#include "IRenderer.h"

namespace Crystal {
	namespace Renderer {

class ImportanceRenderer : public IRenderer
{
public:
	struct Buffer
	{
	};

	ImportanceRenderer();

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}