#pragma once
#include "FrameTimer.h"

FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

float FrameTimer::Mark()
{
	auto old = last;
	last = steady_clock::now();
	const duration<float> timer = last - old;
	return timer.count();
}
