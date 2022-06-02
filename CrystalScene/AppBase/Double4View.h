#pragma once

#include "IWindow.h"

#include "../../Crystal/Math/Vector4d.h"
#include <array>

namespace Crystal {
	namespace UI {

class Double4View : public IWindow
{
public:
	explicit Double4View(const std::string& name);

	Double4View(const std::string& name, const Math::Vector4dd& value);

	void onShow() override;

	Math::Vector4dd getValue() const { return value; }

	void setValue(const glm::vec4& value) { this->value = value; }

private:
	Math::Vector4dd value;
};

	}
}