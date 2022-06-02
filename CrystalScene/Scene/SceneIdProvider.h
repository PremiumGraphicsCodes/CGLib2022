#pragma once

#include "Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace Scene {

class SceneIdProvider : private UnCopyable
{
public:
	explicit SceneIdProvider(int startId) :
		nextId(startId)
	{}

	int getNextId() { return nextId++; }

	void reset(int startId) { this->nextId = startId; }

private:
	int nextId;
};
	}
}