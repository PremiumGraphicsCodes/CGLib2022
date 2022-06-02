#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "PropertyTree.h"

namespace Crystal {
	namespace Command {

class IPropertyTreeFactory : UnCopyable
{
public:
	virtual PropertyTree* create(const std::string& name) const = 0;
};

	}
}