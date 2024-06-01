#pragma once

#include <numeric>

class FrameRate
{
	unsigned int window;
	float* frame_times;
	unsigned int index;

public:
	FrameRate(unsigned int window)
	{
		this->window = window;
		frame_times = new float[window];
		index = 0;

		// Set all elements to 0
		std::fill(frame_times, frame_times + window, 0);
	}

	void add_frame_time(float frame_time)
	{
		if (index >= window)
			index = 0;
		frame_times[index++] = frame_time;
	}

	float get_average_frame_rate()
	{
		float average_frame_time = 0;
		for (unsigned int i = 0; i < window; i++)
			average_frame_time += frame_times[i];
		average_frame_time /= window;
		return 1.0f / average_frame_time;
	}
};