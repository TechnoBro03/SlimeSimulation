#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "thread"

class Settings
{
private:
	unsigned int width, height, frame_rate_limit, average_frame_rate_window, num_agents, num_threads;
	float fade_speed, blur_speed;

    unsigned int sensor_offset, sensor_size;
    float speed, turn_speed, sensor_angle;

    int spawn_pattern;

public:
    // Read settings from path (I know this isn't pretty...)
	Settings(const std::string path)
	{
        std::ifstream file(path);
        if (!file.good())
            throw std::invalid_argument("Could not read file");

        // Width
        std::string line;
        std::getline(file, line);
        std::stringstream ss(line);

        std::string var;
        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        width = std::stoi(var);

        // Height
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        height = std::stoi(var);

        // Frame rate limit
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        frame_rate_limit = std::stoi(var);

        // Average frame rate window
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        average_frame_rate_window = std::stoi(var);

        // Num theads
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        num_threads = std::stoi(var);
        if (num_threads < 1)
            num_threads = 1;
        if (num_threads > std::thread::hardware_concurrency())
            num_threads = std::thread::hardware_concurrency();

        // Fade speed
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        fade_speed = std::stof(var);

        // Blur speed
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        blur_speed = std::stof(var);

        // Num agents
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        num_agents = std::stoi(var);

        // Speed
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        speed = std::stof(var);

        // Turn speed
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        turn_speed = std::stof(var);

        // Sensor offset
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        sensor_offset = std::stof(var);

        // Sensor size
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        sensor_size = std::stoi(var);

        // Sensor angle
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        sensor_angle = std::stof(var);

        // Spawn pattern
        std::getline(file, line);
        ss = std::stringstream(line);

        std::getline(ss, var, ':');
        std::getline(ss, var, ':');
        spawn_pattern = std::stoi(var);
	}

    // Get methods
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
    unsigned int get_num_threads() const
    {
        return num_threads;
    }
    float get_fade_speed() const
    {
        return fade_speed;
    }
    float get_blur_speed() const
    {
        return blur_speed;
    }
    unsigned int get_sensor_offset() const
    {
        return sensor_offset;
    }
    unsigned int get_sensor_size() const
    {
        return sensor_size;
    }
    float get_speed() const
    {
        return speed;
    }
    float get_turn_speed() const
    {
        return turn_speed;
    }
    float get_sensor_angle() const
    {
        return sensor_angle;
    }
    int get_spawn_pattern() const
    {
        return spawn_pattern;
    }
};