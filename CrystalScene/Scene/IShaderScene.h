#pragma once

#include <list>
#include <string>
#include "Crystal/Graphics/Camera.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {

class IShaderScene
{
public:
	explicit IShaderScene(const std::string& name) :
		name(name),
		isVisible_(true)
	{}

	virtual ~IShaderScene() {};

	virtual bool build(Shader::GLObjectFactory& glFactory) = 0;

	virtual void release(Shader::GLObjectFactory& glFactory) = 0;

	virtual void render(const Graphics::Camera& camera) = 0;

	std::string getName() const { return name; }

	void setVisible(const bool isVisible) { this->isVisible_ = isVisible; }

	bool isVisible() const { return isVisible_; }

private:
	std::string name;
	bool isVisible_;
};

	}
}