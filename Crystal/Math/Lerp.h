#pragma once

namespace Crystal {
	namespace Math {

template<typename T>
class Lerp
{
public:
	static T lerp(const T start, const T end, const T value)
	{
		return (value - start) / (end - start);
	}
	
};
	}
}