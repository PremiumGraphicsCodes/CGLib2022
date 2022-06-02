#pragma once
#include <vector>
#include <any>
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

enum class PLYType
{
	CHAR,
	UCHAR,
	SHORT,
	USHORT,
	INT,
	UINT,
	FLOAT,
	DOUBLE,
};

struct PLYPoint
{
	PLYPoint() = default;

	std::vector<std::any> values;

	template<typename T>
	T getValueAs(const size_t index) const
	{
		return std::any_cast<T>(values[index]);
	}
};

struct PLYProperty
{
	PLYProperty() = default;

	PLYProperty(const std::string& name, const PLYType& type) :
		name(name),
		type(type)
	{}

	std::string getTypeName() const {
		return "float";
	}

	static PLYType toType(const std::string& typeName)
	{
		return PLYType::FLOAT;
	}
	

	std::string name;
	PLYType type;
};

struct PLYFile
{
	std::vector<PLYProperty> properties;
	std::vector<PLYPoint> vertices;
};

	}
}