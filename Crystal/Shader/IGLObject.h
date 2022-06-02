#pragma once

namespace Crystal {
	namespace Shader {

class IGLObject
{
public:
	IGLObject() {};

	virtual ~IGLObject() {};

	virtual void clear() = 0;
};
	}
}