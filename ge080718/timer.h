#pragma once
#include <chrono>

typedef std::chrono::steady_clock::time_point Time;

class Timer
{
	Time				_time;
public:
	void start();
	float getElapsedTime() const;
	void reset();
};