#pragma once

namespace Crystal {
	namespace Shape {

template<typename T>
class CircularBuffer
{
public:
	CircularBuffer() {};

	explicit CircularBuffer(size_t size) :
		buffer(size),
		size(size)
	{
		buffer.resize(size);
	}

	void resize(size_t size)
	{
		buffer.resize(size);
		this->size = size;
	}

	T operator[](size_t index) const { return buffer[getActualIndex(index)]; }

	T& operator[](size_t index) { return buffer[getActualIndex(index)]; }

	void set(size_t index, T value) { buffer[getActualIndex(index)] = value; }

	T get(size_t index) { return buffer[getActualIndex(index)]; }

private:
	size_t getActualIndex(size_t index) const { return index % size; }

	std::vector<T> buffer;
	size_t size;
};
	}
}