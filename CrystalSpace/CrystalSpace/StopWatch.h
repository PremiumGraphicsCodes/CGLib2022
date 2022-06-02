#pragma once

#include <chrono>

namespace Crystal {
	namespace Space {

class StopWatch
{
public:
	void start() { startTime = std::chrono::system_clock::now(); }

	void stop() { endTime = std::chrono::system_clock::now(); }

	double getElapsed() {
		return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.0;
	}

private:
	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;
};

	}
}