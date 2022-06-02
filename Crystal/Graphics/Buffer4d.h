#pragma once

#include "ColorRGBA.h"
#include "IBuffer.h"
#include "../Math/Quaternion.h"
#include "../Math/glm.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Buffer4d
{
public:
	Buffer4d() = default;

	Buffer4d(const std::vector<T>& buffer) :
		buffer(buffer)
	{}

	~Buffer4d() = default;

	void add(const Buffer4d<T>& rhs) {
		buffer.insert(buffer.end(), rhs.buffer.begin(), rhs.buffer.end());
	}

	void add(const glm::vec4& v) {
		buffer.push_back(v[0]);
		buffer.push_back(v[1]);
		buffer.push_back(v[2]);
		buffer.push_back(v[3]);
	}

	bool operator==(const Buffer4d<T>& rhs) { return buffer == rhs.buffer; }

	void merge(const Buffer4d<T>& rhs) {
		buffer.insert(buffer.end(), rhs.buffer.begin(), rhs.buffer.end());
	}

	void clear() {
		buffer.clear();
	}

	std::vector<T> get() const { return buffer; }

private:
	std::vector<T> buffer;
};

	}
}
