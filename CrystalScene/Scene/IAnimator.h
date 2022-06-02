#pragma once

namespace Crystal {
	namespace Scene{

class IAnimator
{
public:
	IAnimator() :
		id(-1)
	{}

	explicit IAnimator(const int id) :
		id(id)
	{}

	virtual void step() = 0;

	int getId() const { return id; }

private:
	int id;
};
	}
}