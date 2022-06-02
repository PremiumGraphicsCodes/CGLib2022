#pragma once

#include "IWindow.h"

#include "../../Crystal/Math/Vector4d.h"
#include <array>

namespace Crystal {
	namespace UI {

class Float4View : public IWindow
{
public:
	explicit Float4View(const std::string& name);

	Float4View(const std::string& name, const glm::vec4& value);

	void onShow() override;

	glm::vec4 getValue() const { return value; }

	void setValue(const glm::vec4& value) { this->value = value; }

private:
	glm::vec4 value;
};

	}
}