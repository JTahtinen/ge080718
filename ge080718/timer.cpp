#include "timer.h"

#define CURRENT_TIME std::chrono::high_resolution_clock::now()

void Timer::start()
{
	reset();
}

float Timer::getElapsedTime() const
{
	Time elapsed = CURRENT_TIME;
	std::chrono::duration<float> duration = elapsed - _time;
	return duration.count();
}

void Timer::reset()
{
	_time = CURRENT_TIME;
}