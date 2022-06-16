#pragma once

#include "IView.h"

#include "Vector3dView.h"

#include "../../Crystal/Math/Box3d.h"

namespace Crystal {
	namespace UI {

class Box3dfView : public IView
{
public:
	explicit Box3dfView(const std::string& name);

	Box3dfView(const std::string& name, const Math::Box3df& value);

	Math::Box3df getValue() const;

	void setValue(const Math::Box3df& value);

private:
	Vector3dfView minView;
	Vector3dfView maxView;
};


class Box3dView : public IView
{
public:
	explicit Box3dView(const std::string& name);

	Box3dView(const std::string& name, const Math::Box3dd& value);

	Math::Box3dd getValue() const;

	void setValue(const Math::Box3dd& value);

private:
	Vector3dView minView;
	Vector3dView maxView;
};

	}
}