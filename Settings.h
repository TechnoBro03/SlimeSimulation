#pragma once

class Settings
{
private:
	unsigned int width, height, frame_rate_limit, average_frame_rate_window, num_agents;
	float fade_speed, blur_speed;

public:
	Settings(unsigned int width, unsigned int height, unsigned int frame_rate_limit, unsigned int average_frame_rate_window, unsigned int num_agents, float fade_speed, float blur_speed)
	{
		this->width = width;
		this->height = height;
		this->frame_rate_limit = frame_rate_limit;
		this->average_frame_rate_window = average_frame_rate_window;
		this->num_agents = num_agents;
		this->fade_speed = fade_speed;
		this->blur_speed = blur_speed;
	}

    // Gett methods
    unsigned int get_width() const
    {
        return width;
    }

    unsigned int get_height() const
    {
        return height;
    }

    unsigned int get_frame_rate_limit() const
    {
        return frame_rate_limit;
    }

    unsigned int get_average_frame_rate_window() const
    {
        return average_frame_rate_window;
    }

    unsigned int get_num_agents() const
    {
        return num_agents;
    }

    float get_fade_speed() const
    {
        return fade_speed;
    }

    float get_blur_speed() const
    {
        return blur_speed;
    }
};