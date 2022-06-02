#pragma once

#include "openvdb/openvdb.h"

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Matrix4d.h"

namespace Crystal {
	namespace VDB {

class VDBVolumeImpl
{
public:
	VDBVolumeImpl()
	{
	}

	explicit VDBVolumeImpl(openvdb::FloatGrid::Ptr ptr) :
		ptr(ptr)
	{}

	~VDBVolumeImpl() {}

	openvdb::FloatGrid::Ptr getPtr() { return ptr; }

	void setPtr(openvdb::FloatGrid::Ptr ptr) { this->ptr = ptr; }

	void setScale(const double scale);

	void setScale(const double sx, const double sy, const double sz);

	void setTransformMatrix(const Math::Matrix4dd& matrix);

	void setTranslate(const Math::Vector3dd& v);

private:
	openvdb::FloatGrid::Ptr ptr;
};
	}
}