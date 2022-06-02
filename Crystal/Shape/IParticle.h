#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shape {

class IParticleAttribute
{
public:
	IParticleAttribute() :
		size(1.0f)
	{
	}

	explicit IParticleAttribute(const float size) :
		size(size)
	{}

	~IParticleAttribute()
	{}

public:
	float size;
};

class IParticle
{
public:
	~IParticle()
	{}

	virtual Math::Vector3dd getPosition() const = 0;

	//virtual IParticleAttribute* getIAttribute() const { return nullptr; }
};

	}
}