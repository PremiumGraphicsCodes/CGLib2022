#include "VDBVolumeImpl.h"

#include "Converter.h"

using namespace Crystal::VDB;

void VDBVolumeImpl::setScale(const double scale)
{
	this->getPtr()->setTransform(openvdb::math::Transform::createLinearTransform(scale));
}

void VDBVolumeImpl::setScale(const double sx, const double sy, const double sz)
{
	//openvdb::CoordBBox bbox;
	//this->getPtr()->tree().evalActiveVoxelBoundingBox(bbox);

	openvdb::Mat4R m = openvdb::Mat4R::identity();
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
	this->getPtr()->setTransform(openvdb::math::Transform::createLinearTransform(m));
	//this->getPtr()->tree().pru
}

void VDBVolumeImpl::setTransformMatrix(const Math::Matrix4dd& matrix)
{
	const auto m = Converter::toVDB(matrix);
	this->getPtr()->setTransform(openvdb::math::Transform::createLinearTransform(m));
}

void VDBVolumeImpl::setTranslate(const Math::Vector3dd& v)
{
	const auto vv = Converter::toVDB(v);
	this->getPtr()->transformPtr()->postTranslate(vv);
}
