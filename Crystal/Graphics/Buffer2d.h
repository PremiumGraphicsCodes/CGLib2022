#ifndef __CRYSTAL_GRAPHICS_BUFFER_2D_H__
#define __CRYSTAL_GRAPHICS_BUFFER_2D_H__

#include "../Math/Vector2d.h"
#include "../Math/Vector3d.h"

#include "IBuffer.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Buffer2d {
public:
	Buffer2d() = default;

	Buffer2d(const std::vector<T>& buffer) :
		buffer(buffer)
	{}

	~Buffer2d() = default;

	void add(const Math::Vector2df& v) {
		buffer.push_back(v.x);
		buffer.push_back(v.y);
	}

	void merge(const Buffer2d<T>& rhs) {
		buffer.insert(buffer.end(), rhs.buffer.begin(), rhs.buffer.end());
	}

	void clear() { buffer.clear(); }

	std::vector<T> get() const { return buffer; }

private:
	std::vector<T> buffer;
};

	}
}

#endif